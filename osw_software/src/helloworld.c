/******************************************************************************
* Copyright (C) 2023 Advanced Micro Devices, Inc. All Rights Reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/
/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdint.h>
#include <stdio.h>
#include <xstatus.h>
#include <xil_printf.h>
#include <xbasic_types.h>
#include <sleep.h>

#include "platform.h"

#include "bram.h"
#include "usb_ffb_device.h"
#include "logging.h"
#include "steering_wheel_config.h"

#include "xscutimer.h"
#include "xil_exception.h"
#include "xinterrupt_wrap.h"
#include "xparameters.h"

void receiveFfbMagnitude(int32_t magnitude);
void receiveRotation(WheelRotation rotation);

/* Global variables */
volatile SteeringWheelControllerConfig gwheelControllerConfig = {
    rotation720
};

#define INCREMENTAL_ENCODER_CONVERTION_RATIO     (32768.0/10000)
#define BISSC_ENCODER_CONVERTION_RATIO     (32768.0/4194304)

#define BISSC_ENCODER_CONVERTION_RATIO_BIT_SHIFT 7

#define TIMER_LOAD_VALUE_1MS 1 * ((XPAR_CPU_CORE_CLOCK_FREQ_HZ / 2u) / 1000u)
XScuTimer TimerInstance;

static void TimerIntrHandler(void *CallBackRef)
{
    XScuTimer *TimerInstancePtr = (XScuTimer *) CallBackRef;

    /*
    * Check if the timer counter has expired, checking is not necessary
    * since that's the reason this function is executed, this just shows
    * how the callback reference can be used as a pointer to the instance
    * of the timer counter that expired, increment a shared variable so
    * the main thread of execution can see the timer expired.
    */
/*
    if (XScuTimer_IsExpired(TimerInstancePtr)) {
        XScuTimer_ClearInterruptStatus(TimerInstancePtr);
        TimerExpired++;
        if (TimerExpired == 3) {
            XScuTimer_DisableAutoReload(TimerInstancePtr);
        }
    }
*/
    int32_t position_incremental_enc = 0;
    int32_t position_bissc_enc = 0;
    readWheelPositionFromBram(&position_incremental_enc, &position_bissc_enc);

    // Ratio Convertion
    #ifndef BISSC_ENCODER
        int32_t position = position_incremental_enc * INCREMENTAL_ENCODER_CONVERTION_RATIO * (720.0/rotationEnumToValue(gwheelControllerConfig.wheelRotation));
    #else
//        int32_t position = position_bissc_enc >> BISSC_ENCODER_CONVERTION_RATIO_BIT_SHIFT;
//    int32_t position = position_bissc_enc * BISSC_ENCODER_CONVERTION_RATIO * (720.0/rotationEnumToValue(gwheelControllerConfig.wheelRotation));
    int32_t ratio = 6;
    switch(gwheelControllerConfig.wheelRotation) {
        case rotation360:
            ratio = 6;
            break;
        case rotation540:
            ratio = 4;
            break;
        case rotation720:
            ratio = 3;
            break;
        case rotation1080:
            ratio = 2;
            break;
        default:
            ratio = 3;
            break;
    }

    int32_t position = position_bissc_enc * ratio;
    #endif


    // Limit
/*
    if (position > 32767) {
        position = 32767;
    }
    else if (position < -32768) {
        position = -32768;
    }
*/
    if (position > 12582911) {
        position = 12582911;
    }
    else if (position < -12582912) {
        position = -12582912;
    }

    //printf("Steering wheel position %i rotation %s\n\r", position, rotationEnumToString(gwheelControllerConfig.wheelRotation));

    usbFfbSendPosition(position);
    XScuTimer_ClearInterruptStatus(TimerInstancePtr);
}

int ScuTimerIntrExample(XScuTimer *TimerInstancePtr, UINTPTR BaseAddress)
{
    int Status;
    int LastTimerExpired = 0;
    XScuTimer_Config *ConfigPtr;

    /*
    * Initialize the Scu Private Timer driver.
    */

    ConfigPtr = XScuTimer_LookupConfig(BaseAddress);

    /*
    * This is where the virtual address would be used, this example
    * uses physical address.
    */
    Status = XScuTimer_CfgInitialize(TimerInstancePtr, ConfigPtr,
                    ConfigPtr->BaseAddr);
    if (Status != XST_SUCCESS) {
        return XST_FAILURE;
    }

    /*
    * Perform a self-test to ensure that the hardware was built correctly.
    */
    Status = XScuTimer_SelfTest(TimerInstancePtr);
    if (Status != XST_SUCCESS) {
        return XST_FAILURE;
    }

    /*
    * Connect the device to interrupt subsystem so that interrupts
    * can occur.
    */

    Status = XSetupInterruptSystem(TimerInstancePtr, &TimerIntrHandler,
                    TimerInstancePtr->Config.IntrId,
                    TimerInstancePtr->Config.IntrParent,
                    XINTERRUPT_DEFAULT_PRIORITY);
    /*
    * Enable the timer interrupts for timer mode.
    */
    XScuTimer_EnableInterrupt(TimerInstancePtr);

    if (Status != XST_SUCCESS) {
        return XST_FAILURE;
    }

    /*
    * Enable Auto reload mode.
    */
    XScuTimer_EnableAutoReload(TimerInstancePtr);

    /*
    * Load the timer counter register.
    */

    XScuTimer_LoadTimer(TimerInstancePtr, TIMER_LOAD_VALUE_1MS);

    /*
    * Start the timer counter and then wait for it
    * to timeout a number of times.
    */
    XScuTimer_Start(TimerInstancePtr);

    /*
    * Disable and disconnect the interrupt system.
    */
/*
    XDisconnectInterruptCntrl(TimerInstancePtr->Config.IntrId, TimerInstancePtr->Config.IntrParent);

    XScuTimer_Stop(TimerInstancePtr);
*/
    return XST_SUCCESS;
}

int main()
{
    init_platform();

    LOG("\n\rStarting Controller\n\r");

    if (initBram(TRUE) != XST_SUCCESS) {
        LOG("initBram FAILED\n\r");
        return 0;
    }

    if (usbFfbInit() != XST_SUCCESS) {
        LOG("usbFfbInit FAILED\n\r");
        return 0;
    }

    usbFfbSetForceCallback(receiveFfbMagnitude);
    usbRotationReceivedCallback(receiveRotation);

    usleep(2000000); // TODO LISTEN TO THE 2 "READY" msg from ep1

    if (ScuTimerIntrExample(&TimerInstance, XPAR_SCUTIMER_BASEADDR) != XST_SUCCESS) {
        LOG("SCU Timer Interrupt Example Test Failed\r\n");
        return XST_FAILURE;
    }

    while(TRUE) {
        usleep(1000);
    }

    LOG("Closing Controller\n\r");

    cleanup_platform();
    return 0;
}

void receiveFfbMagnitude(int32_t magnitude)
{
    LOG("FFB magnitude %i\n\r", magnitude);
    writeFfbMagnitudeToBram(magnitude);
}

void receiveRotation(WheelRotation rotation)
{
    //printf("Wheel Rotation %u\n\r", rotationEnumToValue(rotation));
    gwheelControllerConfig.wheelRotation = rotation;

    writeRotationToBram((rotation));
}
