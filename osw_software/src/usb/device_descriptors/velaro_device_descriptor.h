
#include "usb_device_descriptor_definition.h"

// 996 bytes
unsigned char velaro_hid[] = {
        0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
        0x09, 0x04,        // Usage (Joystick)
        0xA1, 0x01,        // Collection (Application)
        0x85, 0x01,        //   Report ID (1)
        0x09, 0x01,        //   Usage (Pointer)
        0xA1, 0x00,        //   Collection (Physical)
        0x09, 0x30,        //     Usage (X)

//        0x16, 0xF0, 0xD8,  //     Logical Minimum (-10000)
//        0x26, 0x10, 0x27,  //     Logical Maximum (10000)
//        0x35, 0x00,        //     Physical Minimum (0)
//        0x47, 0x21, 0x4E, 0x00, 0x00,  //     Physical Maximum (20000)
//        0x75, 0x10,        //     Report Size (16)

//        0x17, 0x00, 0x00, 0xC0, 0xFF,  //     Logical Minimum (-4194304)
//        0x27, 0xFF, 0xFF, 0x3F, 0x00,  //     Logical Maximum (4194303)
//        0x35, 0x00,        //     Physical Minimum (0)
//        0x47, 0x00, 0x00, 0x80, 0x00,  //     Physical Maximum (8388607)
//        0x75, 0x18,        //     Report Size (24)

/*
        0x16, 0x00, 0x80,  //     Logical Minimum (-32768)
        0x26, 0xFF, 0x7F,  //     Logical Maximum (32767)
        0x75, 0x20,        //     Report Size (32)
*/

        0x17, 0x00, 0x00, 0x40, 0xFF,  //     Logical Minimum (-12582912)
        0x27, 0xFF, 0xFF, 0xBF, 0x00,  //     Logical Maximum (12582911)
        0x75, 0x20,        //     Report Size (32)


        0x95, 0x01,        //     Report Count (1)
        0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
/*
        0x09, 0x31,        //     Usage (Y)
        0x15, 0x81,        //     Logical Minimum (-127)
        0x25, 0x7F,        //     Logical Maximum (127)
        0x46, 0xFF, 0x00,  //     Physical Maximum (255)
        0x75, 0x08,        //     Report Size (8)
        0x95, 0x01,        //     Report Count (1)
        0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
*/
        0xC0,              //   End Collection
/*
        0x09, 0x32,        //   Usage (Z)
        0x09, 0x33,        //   Usage (Rx)
        0x09, 0x34,        //   Usage (Ry)
        0x09, 0x35,        //   Usage (Rz)
        0x15, 0x00,        //   Logical Minimum (0)
        0x26, 0xFF, 0x0F,  //   Logical Maximum (4095)
        0x46, 0xFF, 0x0F,  //   Physical Maximum (4095)
        0x75, 0x0C,        //   Report Size (12)
        0x95, 0x04,        //   Report Count (4)
        0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
*/
/*
            0x09, 0x39,        //   Usage (Hat switch)
            0x15, 0x01,        //   Logical Minimum (1)
            0x25, 0x08,        //   Logical Maximum (8)
            0x35, 0x00,        //   Physical Minimum (0)
            0x46, 0x3B, 0x01,  //   Physical Maximum (315)
            0x66, 0x14, 0x00,  //   Unit (System: English Rotation, Length: Centimeter)
            0x75, 0x08,        //   Report Size (8)
            0x95, 0x01,        //   Report Count (1)
            0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
            0x09, 0x39,        //   Usage (Hat switch)
            0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
*/
/*
            0x45, 0x00,        //   Physical Maximum (0)
            0x66, 0x00, 0x00,  //   Unit (None)
            0x05, 0x09,        //   Usage Page (Button)
            0x19, 0x01,        //   Usage Minimum (0x01)
            0x29, 0x20,        //   Usage Maximum (0x20)
            0x15, 0x00,        //   Logical Minimum (0)
            0x25, 0x01,        //   Logical Maximum (1)
            0x45, 0x01,        //   Physical Maximum (1)
            0x75, 0x01,        //   Report Size (1)
            0x95, 0x20,        //   Report Count (32)
            0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
*/
        0x05, 0x0F,        //   Usage Page (PID Page)
        0x09, 0x21,        //   Usage (0x21) (Set Effect Report)
        0xA1, 0x02,        //   Collection (Logical)
        0x09, 0x22,        //     Usage (0x22) (Effect Block Index)
        0x15, 0x01,        //     Logical Minimum (1)
        0x25, 0x07,        //     Logical Maximum (7)
        0x35, 0x01,        //     Physical Minimum (1)
        0x45, 0x07,        //     Physical Maximum (7)
        0x75, 0x08,        //     Report Size (8)
        0x95, 0x01,        //     Report Count (1)
        0x91, 0x02,        //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0x09, 0x25,        //     Usage (0x25) (Effect Type)
        0xA1, 0x02,        //     Collection (Logical)
        0x09, 0x26,        //       Usage (0x26) (ET Constant Force)
        0x09, 0x31,        //       Usage (0x31) (ET Sine)
        0x09, 0x40,        //       Usage (0x40) (ET Spring)
        0x09, 0x41,        //       Usage (0x41) (ET Damper)
        0x09, 0x43,        //       Usage (0x43) (ET Friction)
        0x09, 0x42,        //       Usage (0x42) (ET Inertia)
        0x15, 0x01,        //       Logical Minimum (1)
        0x25, 0x06,        //       Logical Maximum (6)
        0x35, 0x01,        //       Physical Minimum (1)
        0x45, 0x06,        //       Physical Maximum (6)
        0x75, 0x08,        //       Report Size (8)
        0x95, 0x01,        //       Report Count (1)
        0x91, 0x00,        //       Output (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0xC0,              //     End Collection
        0x09, 0x50,        //     Usage (0x50) (Duration)
        0x15, 0x00,        //     Logical Minimum (0)
        0x26, 0x31, 0x75,  //     Logical Maximum (30001)
        0x35, 0x00,        //     Physical Minimum (0)
        0x46, 0x98, 0x3A,  //     Physical Maximum (15000)
        0x66, 0x03, 0x10,  //     Unit (System: English Linear, Time: Seconds)
        0x55, 0xFD,        //     Unit Exponent
        0x75, 0x10,        //     Report Size (16)
        0x95, 0x01,        //     Report Count (1)
        0x91, 0x02,        //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0x09, 0x54,        //     Usage (0x54) (Trigger Repeat Interval)
        0x09, 0x51,        //     Usage (0x51) (Sample Period)
        0x26, 0xFF, 0x00,  //     Logical Maximum (255)
        0x46, 0xFF, 0x7F,  //     Physical Maximum (32767)
        0x75, 0x08,        //     Report Size (8)
        0x95, 0x02,        //     Report Count (2)
        0x91, 0x02,        //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0x55, 0x00,        //     Unit Exponent (0)
        0x66, 0x00, 0x00,  //     Unit (None)
        0x09, 0x52,        //     Usage (0x52) (Gain)
        0x15, 0x00,        //     Logical Minimum (0)
        0x26, 0x10, 0x27,  //     Logical Maximum (10000)
        0x35, 0x00,        //     Physical Minimum (0)
        0x46, 0x10, 0x27,  //     Physical Maximum (10000)
        0x75, 0x10,        //     Report Size (16)
        0x95, 0x01,        //     Report Count (1)
        0x91, 0x02,        //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0x09, 0x53,        //     Usage (0x53) (Trigger Button)
        0x15, 0x01,        //     Logical Minimum (1)
        0x25, 0x08,        //     Logical Maximum (8)
        0x35, 0x01,        //     Physical Minimum (1)
        0x45, 0x08,        //     Physical Maximum (8)
        0x75, 0x08,        //     Report Size (8)
        0x95, 0x01,        //     Report Count (1)
        0x91, 0x02,        //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)

        0x09, 0x55,        //     Usage (0x55) (Axes Enable)
        0xA1, 0x02,        //     Collection (Logical)
        0x05, 0x01,        //       Usage Page (Generic Desktop Ctrls)
        0xA1, 0x00,        //       Collection (Physical)
        0x09, 0x30,        //         Usage (X)
        0x15, 0x00,        //         Logical Minimum (0)
        0x25, 0x01,        //         Logical Maximum (1)
        0x75, 0x01,        //         Report Size (1)
        0x95, 0x01,        //         Report Count (1)
        0x91, 0x02,        //         Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0xC0,              //       End Collection
        0xC0,              //     End Collection

        0x05, 0x0F,        //     Usage Page (PID Page)
        0x09, 0x56,        //     Usage (0x56) (Direction Enable)
        0x95, 0x01,        //     Report Count (1)
        0x91, 0x02,        //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0x95, 0x06,        //     Report Count (6)
        0x91, 0x03,        //     Output (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0x09, 0x57,        //     Usage (0x57) ( Direction)
        0xA1, 0x02,        //     Collection (Logical)
        0x0B, 0x01, 0x00, 0x0A, 0x00,  //       Usage (0x0A0001)
        0x0B, 0x02, 0x00, 0x0A, 0x00,  //       Usage (0x0A0002)
        0x65, 0x14,        //       Unit (System: English Rotation, Length: Centimeter)
        0x55, 0xFE,        //       Unit Exponent
        0x15, 0x00,        //       Logical Minimum (0)
        0x26, 0xFF, 0x00,  //       Logical Maximum (255)
        0x35, 0x00,        //       Physical Minimum (0)
        0x47, 0xA0, 0x8C, 0x00, 0x00,  //       Physical Maximum (35999)
        0x65, 0x00,        //       Unit (None)
        0x75, 0x08,        //       Report Size (8)
        0x95, 0x02,        //       Report Count (2)
        0x91, 0x02,        //       Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0x55, 0x00,        //       Unit Exponent (0)
        0x65, 0x00,        //       Unit (None)
        0xC0,              //     End Collection
        0xC0,              //   End Collection


        0x09, 0x5A,        //   Usage (0x5A) (Set Envelope Report)
        0xA1, 0x02,        //   Collection (Logical)
        0x85, 0x02,        //     Report ID (2)
        0x09, 0x22,        //     Usage (0x22) (Effect Block Index)
        0x15, 0x01,        //     Logical Minimum (1)
        0x25, 0x07,        //     Logical Maximum (7)
        0x35, 0x01,        //     Physical Minimum (1)
        0x45, 0x07,        //     Physical Maximum (7)
        0x75, 0x08,        //     Report Size (8)
        0x95, 0x01,        //     Report Count (1)
        0x91, 0x02,        //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0x09, 0x5B,        //     Usage (0x5B) (Attack Level)
        0x09, 0x5D,        //     Usage (0x5D) (Fade Level)
        0x26, 0xFF, 0x00,  //     Logical Maximum (255)
        0x46, 0x10, 0x27,  //     Physical Maximum (10000)
        0x75, 0x08,        //     Report Size (8)
        0x95, 0x02,        //     Report Count (2)
        0x91, 0x02,        //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0x09, 0x5C,        //     Usage (0x5C) (Attack Time)
        0x09, 0x5E,        //     Usage (0x5E) (Fade Time)
        0x66, 0x03, 0x10,  //     Unit (System: English Linear, Time: Seconds)
        0x55, 0xFD,        //     Unit Exponent
        0x75, 0x08,        //     Report Size (8)
        0x91, 0x02,        //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0x65, 0x00,        //     Unit (None)
        0x55, 0x00,        //     Unit Exponent (0)
        0xC0,              //   End Collection

        0x09, 0x5F,        //   Usage (0x5F) (Set Condition Report)
        0xA1, 0x02,        //   Collection (Logical)
        0x85, 0x03,        //     Report ID (3)
        0x09, 0x22,        //     Usage (0x22) (Effect Block Index)
        0x15, 0x01,        //     Logical Minimum (1)
        0x25, 0x07,        //     Logical Maximum (7)
        0x35, 0x01,        //     Physical Minimum (1)
        0x45, 0x07,        //     Physical Maximum (7)
        0x75, 0x08,        //     Report Size (8)
        0x95, 0x01,        //     Report Count (1)
        0x91, 0x02,        //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0x09, 0x60,        //     Usage (0x60) ( CP Offset)
        0x36, 0x01, 0x80,  //     Physical Minimum (-32767)
        0x46, 0xFF, 0x7F,  //     Physical Maximum (32767)
        0x16, 0x01, 0x80,  //     Logical Minimum (-32767)
        0x26, 0xFF, 0x7F,  //     Logical Maximum (32767)
        0x75, 0x10,        //     Report Size (16)
        0x91, 0x02,        //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0x09, 0x61,        //     Usage (0x61) (Positive Coefficient)
        0x09, 0x62,        //     Usage (0x62) (Negative Coefficient)
        0x36, 0xF0, 0xD8,  //     Physical Minimum (-10000)
        0x46, 0x10, 0x27,  //     Physical Maximum (10000)
        0x16, 0xF0, 0xD8,  //     Logical Minimum (-10000)
        0x26, 0x10, 0x27,  //     Logical Maximum (10000)
        0x95, 0x02,        //     Report Count (2)
        0x91, 0x02,        //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0x09, 0x63,        //     Usage (0x63) (Positive Saturation)
        0x09, 0x64,        //     Usage (0x64) (Negative Saturation)
        0x35, 0x00,        //     Physical Minimum (0)
        0x15, 0x00,        //     Logical Minimum (0)
        0x91, 0x02,        //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0x09, 0x65,        //     Usage (0x65) (Dead Band)
        0x95, 0x01,        //     Report Count (1)
        0x91, 0x02,        //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0xC0,              //   End Collection

        0x09, 0x6E,        //   Usage (0x6E) (Set Periodic Report)
        0xA1, 0x02,        //   Collection (Logical)
        0x85, 0x04,        //     Report ID (4)
        0x09, 0x22,        //     Usage (0x22) (Effect Block Index)
        0x15, 0x01,        //     Logical Minimum (1)
        0x25, 0x07,        //     Logical Maximum (7)
        0x35, 0x01,        //     Physical Minimum (1)
        0x45, 0x07,        //     Physical Maximum (7)
        0x75, 0x08,        //     Report Size (8)
        0x95, 0x01,        //     Report Count (1)
        0x91, 0x02,        //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0x09, 0x71,        //     Usage (0x71) (Phase)
        0x26, 0xFF, 0x00,  //     Logical Maximum (255)
        0x46, 0x10, 0x27,  //     Physical Maximum (10000)
        0x75, 0x08,        //     Report Size (8)
        0x95, 0x01,        //     Report Count (1)
        0x91, 0x02,        //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0x09, 0x70,        //     Usage (0x70) (Magnitude)
        0x26, 0x10, 0x27,  //     Logical Maximum (10000)
        0x75, 0x10,        //     Report Size (16)
        0x95, 0x01,        //     Report Count (1)
        0x91, 0x02,        //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0x09, 0x6F,        //     Usage (0x6F) (Offset)
        0x16, 0xF0, 0xD8,  //     Logical Minimum (-10000)
        0x36, 0xF0, 0xD8,  //     Physical Minimum (-10000)
        0x75, 0x10,        //     Report Size (16)
        0x95, 0x01,        //     Report Count (1)
        0x91, 0x02,        //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0x09, 0x72,        //     Usage (0x72) (Period)
        0x15, 0x00,        //     Logical Minimum (0)
        0x35, 0x00,        //     Physical Minimum (0)
        0x27, 0xFF, 0xFF, 0x00, 0x00,  //     Logical Maximum (65534)
        0x47, 0xFF, 0xFF, 0x00, 0x00,  //     Physical Maximum (65534)
        0x55, 0xFB,        //     Unit Exponent
        0x66, 0x03, 0x10,  //     Unit (System: English Linear, Time: Seconds)
        0x75, 0x10,        //     Report Size (16)
        0x95, 0x01,        //     Report Count (1)
        0x91, 0x02,        //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0x65, 0x00,        //     Unit (None)
        0x55, 0x00,        //     Unit Exponent (0)
        0xC0,              //   End Collection

        0x09, 0x73,        //   Usage (0x73) (Set Constant Force Report)
        0xA1, 0x02,        //   Collection (Logical)
        0x85, 0x05,        //     Report ID (5)
        0x09, 0x22,        //     Usage (0x22) (Effect Block Index)
        0x15, 0x01,        //     Logical Minimum (1)
        0x25, 0x07,        //     Logical Maximum (7)
        0x35, 0x01,        //     Physical Minimum (1)
        0x45, 0x07,        //     Physical Maximum (7)
        0x75, 0x08,        //     Report Size (8)
        0x95, 0x01,        //     Report Count (1)
        0x91, 0x02,        //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0x09, 0x70,        //     Usage (0x70) (Magnitude)
        0x16, 0x78, 0xEC,  //     Logical Minimum (-5000)
        0x26, 0x88, 0x13,  //     Logical Maximum (5000)
        0x36, 0x78, 0xEC,  //     Physical Minimum (-5000)
        0x46, 0x88, 0x13,  //     Physical Maximum (5000)
        0x75, 0x10,        //     Report Size (16)
        0x91, 0x02,        //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0xC0,              //   End Collection

        0x09, 0x77,        //   Usage (0x77) (Effect Operation Report)
        0xA1, 0x02,        //   Collection (Logical)
        0x85, 0x0A,        //     Report ID (10)
        0x09, 0x22,        //     Usage (0x22) (Effect Block Index)
        0x15, 0x01,        //     Logical Minimum (1)
        0x25, 0x07,        //     Logical Maximum (7)
        0x35, 0x01,        //     Physical Minimum (1)
        0x45, 0x07,        //     Physical Maximum (7)
        0x75, 0x08,        //     Report Size (8)
        0x95, 0x01,        //     Report Count (1)
        0x91, 0x02,        //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0x09, 0x78,        //     Usage (0x78) (Effect Operation)
        0xA1, 0x02,        //     Collection (Logical)
        0x09, 0x79,        //       Usage (0x79) (Op Effect Start)
        0x09, 0x7A,        //       Usage (0x7A) (Op Effect Start Solo)
        0x09, 0x7B,        //       Usage (0x7B) (Op Effect Stop)
        0x15, 0x01,        //       Logical Minimum (1)
        0x25, 0x03,        //       Logical Maximum (3)
        0x91, 0x00,        //       Output (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0xC0,              //     End Collection
        0x09, 0x7C,        //     Usage (0x7C) (Loop Count)
        0x15, 0x00,        //     Logical Minimum (0)
        0x26, 0xFF, 0x00,  //     Logical Maximum (255)
        0x46, 0xFF, 0x00,  //     Physical Maximum (255)
        0x91, 0x02,        //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0xC0,              //   End Collection

        0x09, 0x7F,        //   Usage (0x7F) (PID Pool Report)
        0xA1, 0x02,        //   Collection (Logical)
        0x85, 0x01,        //     Report ID (1)
        0x09, 0x80,        //     Usage (0x80) (RAM Pool Size)
        0x15, 0x00,        //     Logical Minimum (0)
        0x26, 0xFF, 0x00,  //     Logical Maximum (255)
        0x35, 0x00,        //     Physical Minimum (0)
        0x46, 0xFF, 0x00,  //     Physical Maximum (255)
        0x75, 0x08,        //     Report Size (8)
        0x95, 0x01,        //     Report Count (1)
        0xB1, 0x02,        //     Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0x09, 0xA8,        //     Usage (0xA8) (Parameter Block Size)
        0xA1, 0x02,        //     Collection (Logical)
        0x09, 0x21,        //       Usage (0x21) (Set Effect Report)
        0x09, 0x5A,        //       Usage (0x5A) (Set Envelope Report)
        0x09, 0x5F,        //       Usage (0x5F) (Set Condition Report)
        0x09, 0x6E,        //       Usage (0x6E) (Set Periodic Report)
        0x09, 0x73,        //       Usage (0x73) (Set Constant Force Report)
        0x75, 0x08,        //       Report Size (8)
        0x95, 0x05,        //       Report Count (5)
        0xB1, 0x02,        //       Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0xC0,              //     End Collection
        0x25, 0x01,        //     Logical Maximum (1)
        0x75, 0x07,        //     Report Size (7)
        0x95, 0x01,        //     Report Count (1)
        0xB1, 0x03,        //     Feature (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0x09, 0xA9,        //     Usage (0xA9) (Device Managed Pool)
        0x75, 0x01,        //     Report Size (1)
        0xB1, 0x02,        //     Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0xC0,              //   End Collection

        0x09, 0x92,        //   Usage (0x92) (PID State Report)
        0xA1, 0x02,        //   Collection (Logical)
        0x85, 0x02,        //     Report ID (2)
        0x09, 0x22,        //     Usage (0x22) (Effect Block Index)
        0x15, 0x01,        //     Logical Minimum (1)
        0x25, 0x07,        //     Logical Maximum (7)
        0x35, 0x01,        //     Physical Minimum (1)
        0x45, 0x07,        //     Physical Maximum (7)
        0x75, 0x08,        //     Report Size (8)
        0x95, 0x01,        //     Report Count (1)
        0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
        0x09, 0x94,        //     Usage (0x94) (Effect Playing)
        0x09, 0xA0,        //     Usage (0xA0) (Actuators Enabled)
        0x09, 0xA4,        //     Usage (0xA4) (Safety Switch)
        0x09, 0xA6,        //     Usage (0xA6) (Actuator Power)
        0x25, 0x01,        //     Logical Maximum (1)
        0x45, 0x01,        //     Physical Maximum (1)
        0x75, 0x01,        //     Report Size (1)
        0x95, 0x04,        //     Report Count (4)
        0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
        0x81, 0x03,        //     Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
        0xC0,              //   End Collection

        0x09, 0x96,        //   Usage (0x96) (PID Device Control)
        0xA1, 0x02,        //   Collection (Logical)
        0x85, 0x0B,        //     Report ID (11)
        0x09, 0x97,        //     Usage (0x97) (DC Enable Actuators)
        0x09, 0x98,        //     Usage (0x98) (DC Disable Actuators)
        0x09, 0x99,        //     Usage (0x99) (DC Stop All Effects)
        0x09, 0x9A,        //     Usage (0x9A) (DC Device Reset)
        0x09, 0x9B,        //     Usage (0x9B) (DC Device Pause)
        0x09, 0x9C,        //     Usage (0x9C) (DC Device Continue)
        0x15, 0x00,        //     Logical Minimum (0)
        0x25, 0x01,        //     Logical Maximum (1)
        0x75, 0x01,        //     Report Size (1)
        0x95, 0x06,        //     Report Count (6)
        0x91, 0x02,        //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0x95, 0x02,        //     Report Count (2)
        0x91, 0x03,        //     Output (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)

        0xC0,              //   End Collection
        0x09, 0xAB,        //   Usage (0xAB) (Create New Effect Report)
        0xA1, 0x02,        //   Collection (Logical)
        0x85, 0x44,        //     Report ID (68)
        0x09, 0x25,        //     Usage (0x25) (Effect Type)
        0xA1, 0x02,        //     Collection (Logical)
        0x09, 0x26,        //       Usage (0x26) (ET Constant Force)
        0x09, 0x31,        //       Usage (0x31) (ET Sine)
        0x09, 0x40,        //       Usage (0x40) (ET Spring)
        0x09, 0x41,        //       Usage (0x41) (ET Damper)
        0x09, 0x43,        //       Usage (0x43) (ET Friction)
        0x09, 0x42,        //       Usage (0x42) (ET Inertia)
        0x15, 0x01,        //       Logical Minimum (1)
        0x25, 0x06,        //       Logical Maximum (6)
        0x35, 0x01,        //       Physical Minimum (1)
        0x45, 0x06,        //       Physical Maximum (6)
        0x75, 0x08,        //       Report Size (8)
        0x95, 0x01,        //       Report Count (1)
        0xB1, 0x00,        //       Feature (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0xC0,              //     End Collection
        0x05, 0x01,        //     Usage Page (Generic Desktop Ctrls)
        0x09, 0x3B,        //     Usage (Byte Count)
        0x15, 0x00,        //     Logical Minimum (0)
        0x26, 0xFF, 0x00,  //     Logical Maximum (255)
        0x35, 0x00,        //     Physical Minimum (0)
        0x46, 0xFF, 0x00,  //     Physical Maximum (255)
        0x75, 0x08,        //     Report Size (8)
        0x95, 0x01,        //     Report Count (1)
        0xB1, 0x02,        //     Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0xC0,              //   End Collection

        0x05, 0x0F,        //   Usage Page (PID Page)
        0x09, 0x90,        //   Usage (0x90) (PID Block Free Report)
        0xA1, 0x02,        //   Collection (Logical)
        0x85, 0x45,        //     Report ID (69)
        0x09, 0x22,        //     Usage (0x22)
        0x15, 0x01,        //     Logical Minimum (1)
        0x25, 0x07,        //     Logical Maximum (7)
        0x35, 0x01,        //     Physical Minimum (1)
        0x45, 0x07,        //     Physical Maximum (7)
        0x75, 0x08,        //     Report Size (8)
        0x95, 0x01,        //     Report Count (1)
        0x91, 0x02,        //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0xC0,              //   End Collection

        0x09, 0x89,        //   Usage (0x89) (PID Block Load Report)
        0xA1, 0x02,        //   Collection (Logical)
        0x85, 0x33,        //     Report ID (51)
        0x09, 0x22,        //     Usage (0x22) (Effect Block Index)
        0x15, 0x01,        //     Logical Minimum (1)
        0x25, 0x07,        //     Logical Maximum (7)
        0x35, 0x01,        //     Physical Minimum (1)
        0x45, 0x07,        //     Physical Maximum (7)
        0x75, 0x08,        //     Report Size (8)
        0x95, 0x01,        //     Report Count (1)
        0xB1, 0x02,        //     Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0x09, 0x8B,        //     Usage (0x8B) (Block Load Status)
        0xA1, 0x02,        //     Collection (Logical)
        0x09, 0x8C,        //       Usage (0x8C) (Block Load Success)
        0x09, 0x8D,        //       Usage (0x8D) (Block Load Full)
        0x09, 0x8E,        //       Usage (0x8E) (Block Load Error)
        0x15, 0x01,        //       Logical Minimum (1)
        0x25, 0x03,        //       Logical Maximum (3)
        0x35, 0x01,        //       Physical Minimum (1)
        0x45, 0x03,        //       Physical Maximum (3)
        0x75, 0x08,        //       Report Size (8)
        0x95, 0x01,        //       Report Count (1)
        0xB1, 0x00,        //       Feature (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0xC0,              //     End Collection
        0x09, 0xAC,        //     Usage (0xAC) (RAM Pool Available)
        0x15, 0x00,        //     Logical Minimum (0)
        0x26, 0xFF, 0x00,  //     Logical Maximum (255)
        0x35, 0x00,        //     Physical Minimum (0)
        0x46, 0xFF, 0x00,  //     Physical Maximum (255)
        0x75, 0x08,        //     Report Size (8)
        0x95, 0x01,        //     Report Count (1)
        0xB1, 0x02,        //     Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0xC0,              //   End Collection

        0x09, 0x7D,        //   Usage (0x7D)
        0xA1, 0x02,        //   Collection (Logical)
        0x85, 0x40,        //     Report ID (64)
        0x09, 0x7E,        //     Usage (0x7E)
        0x26, 0x10, 0x27,  //     Logical Maximum (10000)
        0x46, 0x10, 0x27,  //     Physical Maximum (10000)
        0x75, 0x10,        //     Report Size (16)
        0x95, 0x01,        //     Report Count (1)
        0x91, 0x02,        //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0xC0,              //   End Collection
//        0x06, 0x00, 0xFF,  //   Usage Page (Vendor Defined 0xFF00)
//        0x09, 0x01,        //   Usage (0x01)
//        0xA1, 0x02,        //   Collection (Logical)
//        0x15, 0x00,        //     Logical Minimum (0)
//        0x26, 0xFF, 0x00,  //     Logical Maximum (255)
//        0x75, 0x08,        //     Report Size (8)
//        0x85, 0x80,        //     Report ID (-128)
//        0x95, 0x08,        //     Report Count (8)
//        0x09, 0x01,        //     Usage (0x01)
//        0xB1, 0x02,        //     Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
//        0x09, 0x01,        //     Usage (0x01)
//        0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
//        0x85, 0x90,        //     Report ID (-112)
//        0x95, 0x01,        //     Report Count (1)
//        0x09, 0x01,        //     Usage (0x01)
//        0xB1, 0x02,        //     Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
//        0x85, 0xEE,        //     Report ID (-18)
//        0x95, 0x04,        //     Report Count (4)
//        0x09, 0x01,        //     Usage (0x01)
//        0xB1, 0x02,        //     Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
//        0xC0,              //   End Collection
        0x06, 0x01, 0xFF,  //   Usage Page (Vendor Defined 0xFF01)
        0x09, 0x01,        //   Usage (0x01) (Alejandro01 - rotation_range)
        0xA1, 0x02,        //   Collection (Logical)
        0x85, 0x9C,        //     Report ID (-100)
        0x09, 0x01,        //     Usage (0x03)
        0x15, 0x00,        //     Logical Minimum (0)
        0x26, 0xFF, 0x00,  //     Logical Maximum (3)
        0x75, 0x08,        //     Report Size (8)
        0x95, 0x08,        //     Report Count (1)
        0x91, 0x02,        //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0xC0,              //   End Collection
        0x09, 0x01,        //   Usage (0x01) (Alejandro01 - rotation_offset)
        0xA1, 0x02,        //   Collection (Logical)
        0x85, 0x9B,        //     Report ID (-101)
        0x09, 0x01,        //     Usage (0x03)
        0x17, 0x00, 0x00, 0x40, 0xFF,  //     Logical Minimum (-12582912)
        0x27, 0xFF, 0xFF, 0xBF, 0x00,  //     Logical Maximum (12582911)
        0x75, 0x20,        //     Report Size (32)
        0x95, 0x08,        //     Report Count (1)
        0x91, 0x02,        //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0xC0,              //   End Collection
        0xC0,              // End Collection
    };

USB_STD_DEV_DESC velaro_deviceDesc = {
        sizeof(USB_STD_DEV_DESC),       /* bLength */
        USB_DEVICE_DESC,                /* bDescriptorType */
        be2les(0x0200),                 /* bcdUSB 2.0 */
        0x00,                           /* bDeviceClass */
        0x00,                           /* bDeviceSubClass */
        0x00,                           /* bDeviceProtocol */
        USB_ENDPOINT0_MAXP,             /* bMaxPackedSize0 */
        be2les(0x0d7d),                 /* idVendor */
        be2les(0x0100),                 /* idProduct */
        be2les(0x0100),                 /* bcdDevice */
        0x01,                           /* iManufacturer */
        0x02,                           /* iProduct */
        0x03,                           /* iSerialNumber */
        0x01                            /* bNumConfigurations */
    };

USB_CONFIG velaro_configDesc = {
    /* Std Config 9 bytes */
    {
        sizeof(USB_STD_CFG_DESC),   /* bLength */
        USB_CONFIG_DESC,            /* bDescriptorType */
        be2les(sizeof(USB_CONFIG)), /* wTotalLength */
        0x01,                       /* bNumInterfaces */
        0x01,                       /* bConfigurationValue */
        0x04,                       /* iConfiguration */
        0xc0,                       /* bmAttribute */
        0x00                        /* bMaxPower  */
    },

    /* Interface Config 9 bytes */
    {
        sizeof(USB_STD_IF_DESC),    /* bLength */
        USB_INTERFACE_CFG_DESC,     /* bDescriptorType */
        0x00,                       /* bInterfaceNumber */
        0x00,                       /* bAlternateSetting */
        0x02,                       /* bNumEndPoints */
        0x03,                       /* bInterfaceClass */
        0x00,                       /* bInterfaceSubClass */
        0x00,                       /* bInterfaceProtocol */
        0x05                        /* iInterface */
    },
    /* HID Descriptor 9 bytes */
    {
        sizeof(USB_STD_HID_DESC),   // Longitud del descriptor HID
        0x21,                       // Tipo de descriptor (HID)
        be2les(0x0111),             // Versiï¿½n HID 1.11
        0x00,                       // Paï¿½s
        0x01,                       // Nï¿½mero de descriptores HID
        0x22,                       // Tipo de descriptor (Reporte)
        be2les(sizeof(velaro_hid)),   // Longitud del descriptor de reporte
    },
    /* Endpoint IN 7 bytes */
    {
        sizeof(USB_STD_HID_EP_DESC),// Longitud del descriptor de endpoint
        0x05,                       // Tipo de descriptor (Endpoint)
        0x81,                       // Direcciï¿½n (IN, Endpoint 1)
        0x03,                       // Tipo de transferencia (Interrupciï¿½n)
        be2les(0x0010),             // Tamaï¿½o mï¿½ximo de paquete (8 bytes)
        0x01                        // Intervalo de sondeo (10 ms)
    },
    /* Endpoint OUT 7 bytes */
    {
        sizeof(USB_STD_HID_EP_DESC),// Longitud del descriptor de endpoint
        0x05,                       // Tipo de descriptor (Endpoint)
        0x01,                       // Direcciï¿½n (OUT endpoint 1)
        0x03,                       // Tipo de transferencia (Interrupciï¿½n)
        be2les(0x0010),             // Tamaï¿½o mï¿½ximo de paquete (8 bytes)
        0x01                        // Intervalo de sondeo (10 ms)
    }
};
