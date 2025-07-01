
#include <stdint.h>
#include <xbasic_types.h>
#include <xstatus.h>
#include <xusbps.h>
#include <xscugic.h>
#include <xil_cache.h>
#include <xusbps.h>
#include <xinterrupt_wrap.h>
#include "usb_hid_device.h"
#include "xparameters.h"
#include "xparameters_ps.h"
#include "usb_hid_setup_endpoint.h"
#include "usb_hid_data_endpoint.h"
#include "logging.h"
#include "velaro_hid_report.h"

/* Defines */
#define BUFFER_MEMORY_SIZE (64 * 1024)

/* Local variables */
static XScuGic IntcInstance; /* The instance of the IRQ Controller */
static XUsbPs UsbInstance; /* The instance of the USB Controller */
uint8_t Buffer[BUFFER_MEMORY_SIZE];
static volatile int NumIrqs = 1;
static volatile int num_Ep0_requests = 1;
static volatile int num_Ep1_requests = 1;

/* Fordward declaration */
int usbInit();
static int _usbSetupIntrSystem();
static void _usbDisableIntrSystem();
static void UsbIntrHandler(void *CallBackRef, u32 Mask);
static void XUsbPs_Ep0EventHandler(void *CallBackRef, u8 EpNum, u8 EventType, void *Data);
static void XUsbPs_Ep1EventHandler(void *CallBackRef, u8 EpNum, u8 EventType, void *Data);
static void XUsbPs_Ep1EventHandlerIn(void *CallBackRef, u8 EpNum, u8 EventType, void *Data);

/* Public methods */
int usbInit() {
    int	Status;
    uint8_t	*MemPtr = NULL;
    const uint8_t NumEndpoints = 2;
    XUsbPs_Config *UsbConfigPtr;
    XUsbPs_DeviceConfig	DeviceConfig;

    #ifdef SDT
        LOG("USB %u LookupConfig SDT DEFINED\n\r");
    #endif

    /* USB config find */
    UsbConfigPtr = XUsbPs_LookupConfig(XPAR_XUSBPS_0_BASEADDR);
    if (UsbConfigPtr == NULL) {
        LOG("USB n%u confing not found.\n\r", XPAR_XUSBPS_0_BASEADDR);
        goto out;
    }

    // USB controller init
    Status = XUsbPs_CfgInitialize(&UsbInstance, UsbConfigPtr, UsbConfigPtr->BaseAddress);
    if (Status != XST_SUCCESS) {
        LOG("USB n%u initialization failed\n\r", XPAR_XUSBPS_0_BASEADDR);
        goto out;
    }

    /* Interupt system init */
    Status = XSetupInterruptSystem(&UsbInstance, &XUsbPs_IntrHandler,
                    UsbConfigPtr->IntrId,
                    UsbConfigPtr->IntrParent,
                    XINTERRUPT_DEFAULT_PRIORITY);
    if (Status != XST_SUCCESS) {
        LOG("USB interruptions initialization failed\n");
        goto out;
    }

    DeviceConfig.EpCfg[0].Out.Type		= XUSBPS_EP_TYPE_CONTROL;
    DeviceConfig.EpCfg[0].Out.NumBufs	= 2;
    DeviceConfig.EpCfg[0].Out.BufSize	= 64;
    DeviceConfig.EpCfg[0].Out.MaxPacketSize	= 64;
    DeviceConfig.EpCfg[0].In.Type		= XUSBPS_EP_TYPE_CONTROL;
    DeviceConfig.EpCfg[0].In.NumBufs	= 2;
    DeviceConfig.EpCfg[0].In.MaxPacketSize	= 64;

    DeviceConfig.EpCfg[1].Out.Type		= XUSBPS_EP_TYPE_INTERRUPT;
    DeviceConfig.EpCfg[1].Out.NumBufs	= 16;
    DeviceConfig.EpCfg[1].Out.BufSize	= 512;
    DeviceConfig.EpCfg[1].Out.MaxPacketSize	= 512;
    DeviceConfig.EpCfg[1].In.Type		= XUSBPS_EP_TYPE_INTERRUPT;
    DeviceConfig.EpCfg[1].In.NumBufs	= 16;
    DeviceConfig.EpCfg[1].In.MaxPacketSize	= 512;

    DeviceConfig.NumEndpoints = NumEndpoints;

    MemPtr = (uint8_t *)&Buffer[0];
    memset(MemPtr, 0, BUFFER_MEMORY_SIZE);
    Xil_DCacheFlushRange((uint32_t) MemPtr, BUFFER_MEMORY_SIZE);

    /* Finish the configuration of the DeviceConfig structure and configure
    * the DEVICE side of the controller.
    */
    DeviceConfig.DMAMemPhys = (uint32_t) MemPtr;

    /* Configure Device */
    Status = XUsbPs_ConfigureDevice(&UsbInstance, &DeviceConfig);
    if (Status != XST_SUCCESS) {
        LOG("USB device config failed\n");
		goto out;
    }

    /* Set the handler for receiving frames. */
    Status = XUsbPs_IntrSetHandler(&UsbInstance,
                    &UsbIntrHandler,
                    NULL,
                    XUSBPS_IXR_UE_MASK
                    | XUSBPS_IXR_PC_MASK
                    | XUSBPS_IXR_UR_MASK
                    | XUSBPS_IXR_SLE_MASK
                    | XUSBPS_IXR_HCH_MASK);
    if (XST_SUCCESS != Status) {
		goto out;
    }


    /* Set the handler for handling endpoint 0 events. This is where we
    * will receive and handle the Setup packet from the host.
    */
    Status = XUsbPs_EpSetHandler(&UsbInstance, 0,
                    XUSBPS_EP_DIRECTION_OUT,
                    XUsbPs_Ep0EventHandler, &UsbInstance);

    /* Set the handler for handling endpoint 1 events.
    *
    * Note that for this example we do not need to register a handler for
    * TX complete events as we only send data using static data buffers
    * that do not need to be free()d or returned to the OS after they have
    * been sent.
    */
    Status = XUsbPs_EpSetHandler(&UsbInstance, 1,
                    XUSBPS_EP_DIRECTION_OUT,
                    XUsbPs_Ep1EventHandler, &UsbInstance);
    Status = XUsbPs_EpSetHandler(&UsbInstance, 1,
                    XUSBPS_EP_DIRECTION_IN,
                    XUsbPs_Ep1EventHandlerIn, &UsbInstance);

    /* Enable the interrupts. */
    XUsbPs_IntrEnable(&UsbInstance, XUSBPS_IXR_UR_MASK | XUSBPS_IXR_UI_MASK);

    /* Start the USB engine */
    XUsbPs_Start(&UsbInstance);

    return XST_SUCCESS;

out:

    XUsbPs_Stop(&UsbInstance);
    XUsbPs_IntrDisable(&UsbInstance, XUSBPS_IXR_ALL);
    XDisconnectInterruptCntrl(UsbConfigPtr->IntrId, UsbConfigPtr->IntrParent);

    (int) XUsbPs_IntrSetHandler(&UsbInstance, NULL, NULL, 0);

    /* Free allocated memory.
    */
    if (NULL != UsbInstance.UserDataPtr) {
        free(UsbInstance.UserDataPtr);
    }
    return XST_FAILURE;
}

static void UsbIntrHandler(void *CallBackRef, u32 Mask)
{
    //XUsbPs_StartTimer0()
    //TODO handle usb interrupt

    LOG("UsbIntrHandler %d\n", NumIrqs++);

    switch (Mask) {
        case XUSBPS_IXR_UE_MASK:
        xil_printf("XUSBPS_IXR_UE_MASK\n");
        break;
        case XUSBPS_IXR_PC_MASK:
        xil_printf("XUSBPS_IXR_PC_MASK\n");
        break;
        case XUSBPS_IXR_UR_MASK:
        xil_printf("XUSBPS_IXR_UR_MASK\n");
        break;
        case XUSBPS_IXR_SLE_MASK:
        xil_printf("XUSBPS_IXR_SLE_MASK\n");
        break;
        case XUSBPS_IXR_HCH_MASK:
        xil_printf("XUSBPS_IXR_HCH_MASK\n");
        break;
    }
}

static void XUsbPs_Ep0EventHandler(void *CallBackRef, u8 EpNum, u8 EventType, void *Data)
{
    XUsbPs *InstancePtr;
    int Status;
    XUsbPs_SetupData SetupData;
    u8	*BufferPtr;
    u32	BufferLen;
    u32	Handle;

    LOG("XUsbPs_Ep0EventHandler n%d EventType%u\n", num_Ep0_requests++, EventType);
    Xil_AssertVoid(NULL != CallBackRef);

    InstancePtr = (XUsbPs *) CallBackRef;

    switch (EventType) {

        /* Handle the Setup Packets received on Endpoint 0. */
        case XUSBPS_EP_EVENT_SETUP_DATA_RECEIVED:
            Status = XUsbPs_EpGetSetupData(InstancePtr, EpNum, &SetupData);
            if (XST_SUCCESS == Status) {
                /* Handle the setup packet. */
                (int) HandleSetupPacket(InstancePtr,
                                &SetupData);
            }
            break;

        /* We get data RX events for 0 length packets on endpoint 0. We receive
        * and immediately release them again here, but there's no action to be
        * taken.
        */
        case XUSBPS_EP_EVENT_DATA_RX:
            // Get the data buffer.
            Status = XUsbPs_EpBufferReceive(InstancePtr,
                        EpNum, &BufferPtr,
                        &BufferLen,
                        &Handle);
            if (XST_SUCCESS == Status) {
                // Return the buffer.
                XUsbPs_EpBufferRelease(Handle);
            }
            break;

        default:
            /* Unhandled event. Ignore. */
            break;
    }
}

static void XUsbPs_Ep1EventHandler(void *CallBackRef, u8 EpNum, u8 EventType, void *Data)
{
    XUsbPs *InstancePtr;
    int Status;
    u8	*BufferPtr;
    u32	BufferLen;
    u32 InavalidateLen;
    u32	Handle;

    LOG("XUsbPs_Ep1EventHandler n%d EventType%u\n", num_Ep1_requests++, EventType);

    Xil_AssertVoid(NULL != CallBackRef);

    InstancePtr = (XUsbPs *) CallBackRef;

    switch (EventType) {
        case XUSBPS_EP_EVENT_DATA_RX:
            // Get the data buffer.
            Status = XUsbPs_EpBufferReceive(InstancePtr, EpNum,
                            &BufferPtr, &BufferLen, &Handle);
            /* Invalidate the Buffer Pointer */
            InavalidateLen =  BufferLen;
            if (BufferLen % 32) {
                InavalidateLen = (BufferLen / 32) * 32 + 32;
            }

            Xil_DCacheInvalidateRange((unsigned int)BufferPtr,
                        InavalidateLen);
            if (XST_SUCCESS == Status) {
                // Handle the interrupt.
                HandleInterruptDataPacket(InstancePtr, EpNum, BufferPtr, BufferLen);

                // Release the buffer.
                XUsbPs_EpBufferRelease(Handle);
            }
            break;

        default:
            /* Unhandled event. Ignore. */
            break;
    }
}

static void XUsbPs_Ep1EventHandlerIn(void *CallBackRef, u8 EpNum, u8 EventType, void *Data)
{
    XUsbPs *InstancePtr;
    int Status;
    u8	*BufferPtr;
    u32	BufferLen;
    u32 InavalidateLen;
    u32	Handle;

    // TODO RECEIVE THE 2 MESSAGES RECEVICE IN EP1 THAT SAYS HOST IS READY TO RECEIVE INTERRUPTS
    LOG("XUsbPs_Ep1EventHandlerIN EventType%u\n", EventType);

    Xil_AssertVoid(NULL != CallBackRef);

    InstancePtr = (XUsbPs *) CallBackRef;

    switch (EventType) {
        case XUSBPS_EP_EVENT_DATA_RX:
            LOG("XUSBPS_EP_EVENT_DATA_RX\n");
            break;
        case XUSBPS_EP_EVENT_DATA_TX:
            LOG("XUSBPS_EP_EVENT_DATA_TX\n");
            break;

        default:
            /* Unhandled event. Ignore. */
            break;
    }
}

int usbSendPositionEnp1(int32_t position)
{
    USB_HID_JOYSTICK_REPORT report;
    report.reportId = JOYSTICK_REPORT_ID;
    report.xPosition = position;

    int Status = XUsbPs_EpBufferSend(&UsbInstance, 1, (const u8 *) &report, sizeof(report));
    if (XST_SUCCESS != Status) {
        LOG("XUsbPs_EpBufferSend Failed Status %u \n\r", Status);
    }
    return Status;
}

int usbReceiveMagnitudeEnp0(void (*ptr)(int32_t magnitude))
{
    registerMagnitudeCallback(ptr);
}

int usbReceiveRotationRangeEnp0(void (*ptr)(WheelRotation rotation))
{
    registerRotationRangeCallback(ptr);
}

int usbReceiveRotationOffsetEnp0(void (*ptr)(int32_t rotation))
{
    registerRotationOffsetCallback(ptr);
}