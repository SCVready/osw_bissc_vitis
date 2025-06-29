
#ifndef __USB_DEVICE_DESCRIPTOR_H_
#define __USB_DEVICE_DESCRIPTOR_H_

#include <xbasic_types.h>

#define USB_ENDPOINT0_MAXP          0x40

#define USB_DEVICE_DESC             0x01
#define USB_CONFIG_DESC             0x02
#define USB_STRING_DESC             0x03
#define USB_INTERFACE_CFG_DESC      0x04
#define USB_ENDPOINT_CFG_DESC       0x05

#define be2le(val)  (u32)(val)
#define be2les(x)   (u16) (x)

#pragma pack(push, 1)
typedef struct {
    u8  bLength;
    u8  bDescriptorType;
    u16 bcdUSB;
    u8  bDeviceClass;
    u8  bDeviceSubClass;
    u8  bDeviceProtocol;
    u8  bMaxPacketSize0;
    u16 idVendor;
    u16 idProduct;
    u16 bcdDevice;
    u8  iManufacturer;
    u8  iProduct;
    u8  iSerialNumber;
    u8  bNumConfigurations;
} USB_STD_DEV_DESC;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
    u8  bLength;
    u8  bDescriptorType;
    u16 wTotalLength;
    u8  bNumInterfaces;
    u8  bConfigurationValue;
    u8  iConfiguration;
    u8  bmAttributes;
    u8  bMaxPower;
} USB_STD_CFG_DESC;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
    u8  bLength;
    u8  bDescriptorType;
    u8  bInterfaceNumber;
    u8  bAlternateSetting;
    u8  bNumEndPoints;
    u8  bInterfaceClass;
    u8  bInterfaceSubClass;
    u8  bInterfaceProtocol;
    u8  iInterface;
} USB_STD_IF_DESC;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
    u8  bLength;
    u8  bDescriptorType;
    u16  bcdHID;
    u8 bCountryCode;
    u8  bNumDescriptors;
    u8  bDescriptorTypeReport;
    u16  bDescriptorLength ;
} USB_STD_HID_DESC;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
    u8  bLength;
    u8  bDescriptorType;
    u8  bEndpointAddress;
    u8  bmAttributes;
    u16 wMaxPacketSize;
    u8  bInterval;
} USB_STD_HID_EP_DESC;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
    u8  bLength;
    u8  bDescriptorType;
    u8  bEndpointAddress;
    u8  bmAttributes;
    u16 wMaxPacketSize;
    u8  bInterval;
} USB_STD_EP_DESC;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
    u8  bLength;
    u8  bDescriptorType;
    u16 wLANGID[1];
} USB_STD_STRING_DESC;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
    USB_STD_CFG_DESC stdCfg;
    USB_STD_IF_DESC ifCfg;
    USB_STD_HID_DESC hidCfg;
    USB_STD_HID_EP_DESC hidEpInCfg;
    USB_STD_HID_EP_DESC hidEpOutCfg;
} USB_CONFIG;
#pragma pack(pop)

#endif
