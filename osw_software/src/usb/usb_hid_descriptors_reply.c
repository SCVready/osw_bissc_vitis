
#include <string.h>
#include <xusbps.h>
#include "usb_device_descriptor_definition.h"
#include "velaro_device_descriptor.h"

/************************** Constant Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/**************************** Type Definitions *******************************/

/*****************************************************************************
* This function returns the device descriptor for the device.
* @param    BufPtr is pointer to the buffer that is to be filled with the descriptor.
* @param    BufLen is the size of the provided buffer.
* @return   Length of the descriptor in the buffer on success. 0 on error.
******************************************************************************/
u32 XUsbPs_Ch9SetupDevDescReply(u8 *BufPtr, u32 BufLen)
{
    USB_STD_DEV_DESC deviceDesc = velaro_deviceDesc;

    /* Check buffer pointer is there and buffer is big enough. */
    if (!BufPtr) {
        return 0;
    }

    if (BufLen < sizeof(USB_STD_DEV_DESC)) {
        return 0;
    }

    memcpy(BufPtr, &deviceDesc, sizeof(USB_STD_DEV_DESC));

    return sizeof(USB_STD_DEV_DESC);
}

/*****************************************************************************
* This function returns the hid report descriptor for the device.
* @param    BufPtr is pointer to the buffer that is to be filled with the descriptor.
* @param    BufLen is the size of the provided buffer.
* @return   Length of the descriptor in the buffer on success. 0 on error.
******************************************************************************/
u32 XUsbPs_Ch9SetupHidReportDescReply(u8 *BufPtr, u32 BufLen)
{
    /* Check buffer pointer is there and buffer is big enough. */
    if (!BufPtr) {
        return 0;
    }

    if (BufLen < sizeof(velaro_hid)) {
        return 0;
    }

    memcpy(BufPtr, &velaro_hid, sizeof(velaro_hid));

    return sizeof(velaro_hid);
}

/*****************************************************************************
* This function returns the configuration descriptor for the device.
* @param    BufPtr is pointer to the buffer that is to be filled with the descriptor.
* @param    BufLen is the size of the provided buffer.
* @return   Length of the descriptor in the buffer on success. 0 on error.
******************************************************************************/
u32 XUsbPs_Ch9SetupCfgDescReply(u8 *BufPtr, u32 BufLen)
{
    USB_CONFIG configDesc = velaro_configDesc;

    /* Check buffer pointer is OK and buffer is big enough. */
    if (!BufPtr) {
        return 0;
    }

    if (BufLen < sizeof(USB_CONFIG)) {
        return 0;
    }

    memcpy(BufPtr, &configDesc, sizeof(USB_CONFIG));

    return sizeof(USB_CONFIG);
}

/*****************************************************************************
* This function returns a string descriptor for the given index.
* @param    BufPtr is a  pointer to the buffer that is to be filled with the descriptor.
* @param    BufLen is the size of the provided buffer.
* @param    Index is the index of the string for which the descriptor is requested.
* @return   Length of the descriptor in the buffer on success. 0 on error.
******************************************************************************/
u32 XUsbPs_Ch9SetupStrDescReply(u8 *BufPtr, u32 BufLen, u8 Index)
{
    int i;

    static char *StringList[] = {
        "UNUSED",
        "SCVready",
        "Velaro",
        "000001",
        "SteeringWheel",
        "Standard",
    };
    char *String;
    u32 StringLen;
    u32 DescLen;
    u8 TmpBuf[128];

    USB_STD_STRING_DESC *StringDesc;

    if (!BufPtr) {
        return 0;
    }

    if (Index >= sizeof(StringList) / sizeof(char *)) {
        return 0;
    }

    String = StringList[Index];
    StringLen = strlen(String);

    StringDesc = (USB_STD_STRING_DESC *) TmpBuf;

    /* Index 0 is special as we can not represent the string required in
    * the table above. Therefore we handle index 0 as a special case.
    */
    if (0 == Index) {
        StringDesc->bLength = 4;
        StringDesc->bDescriptorType = USB_STRING_DESC;
        StringDesc->wLANGID[0] = be2les(0x0409);
    }
    /* All other strings can be pulled from the table above. */
    else {
        StringDesc->bLength = StringLen * 2 + 2;
        StringDesc->bDescriptorType = USB_STRING_DESC;

        for (i = 0; i < StringLen; i++) {
            StringDesc->wLANGID[i] = be2les((u16) String[i]);
        }
    }
    DescLen = StringDesc->bLength;

    /* Check if the provided buffer is big enough to hold the descriptor. */
    if (DescLen > BufLen) {
        return 0;
    }

    memcpy(BufPtr, StringDesc, DescLen);

    return DescLen;
}


/*****************************************************************************
* This function handles a "set configuration" request.
* @param    InstancePtr is a pointer to XUsbPs instance of the controller.
* @param    ConfigIdx is the Index of the desired configuration.
* @return   None
******************************************************************************/
void XUsbPs_SetConfiguration(XUsbPs *InstancePtr, int ConfigIdx)
{
    Xil_AssertVoid(InstancePtr != NULL);

    /* We only have one configuration. Its index is 1. Ignore anything
    * else.
    */
    if (1 != ConfigIdx) {
        return;
    }

    XUsbPs_EpEnable(InstancePtr, 1, XUSBPS_EP_DIRECTION_OUT);
    XUsbPs_EpEnable(InstancePtr, 1, XUSBPS_EP_DIRECTION_IN);

    /* Set BULK mode for both directions.  */
    XUsbPs_SetBits(InstancePtr, XUSBPS_EPCR1_OFFSET,
            XUSBPS_EPCR_TXT_INTR_MASK |
            XUSBPS_EPCR_RXT_INTR_MASK |
            XUSBPS_EPCR_TXR_MASK |
            XUSBPS_EPCR_RXR_MASK);

    /* Prime the OUT endpoint. */
    XUsbPs_EpPrime(InstancePtr, 1, XUSBPS_EP_DIRECTION_OUT);
}

/****************************************************************************
 * This function is called by Chapter9 handler when SET_CONFIGURATION command
 * is received from Host.
* @param    InstancePtr is pointer to XUsbPs instance of the controller.
* @param    SetupData is the setup packet received from Host.
*
* @return   XST_SUCCESS if successful, XST_FAILURE if unsuccessful.
* @note
*   Non control endpoints must be enabled after SET_CONFIGURATION
*   command since hardware clears all previously enabled endpoints
*   except control endpoints when this command is received.
 *****************************************************************************/
void XUsbPs_SetConfigurationApp(XUsbPs *InstancePtr, XUsbPs_SetupData *SetupData)
{
    (void)InstancePtr;
    (void)SetupData;
}

/****************************************************************************
 * This function is called by Chapter9 handler when SET_CONFIGURATION command
 * or SET_INTERFACE command is received from Host.
 * @param	InstancePtr is pointer to XUsbPs instance of the controller.
 * @param	SetupData is the setup packet received from Host.
 *****************************************************************************/
void XUsbPs_SetInterfaceHandler(XUsbPs *InstancePtr, XUsbPs_SetupData *SetupData)
{
    (void)InstancePtr;
    (void)SetupData;
}
