/***************************************************************************//**
 * @file     descriptors.c
 * @brief    This file define the descriptors of Vendor LBK device. 
 * @version  2.0.0
 *
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
/*!<Includes */
#include "NuMicro.h"
#include "vendor_lbk.h"

/*----------------------------------------------------------------------------*/
/*!<USB Device Descriptor */
uint8_t gu8DeviceDescriptor[] =
{
    LEN_DEVICE,     /* bLength */
    DESC_DEVICE,    /* bDescriptorType */
    0x10, 0x01,     /* bcdUSB */
    0x00,           /* bDeviceClass */
    0x00,           /* bDeviceSubClass */
    0x00,           /* bDeviceProtocol */
    EP0_MAX_PKT_SIZE,   /* bMaxPacketSize0 */
    /* idVendor */
    USBD_VID & 0x00FF,
    ((USBD_VID & 0xFF00) >> 8),
    /* idProduct */
    USBD_PID & 0x00FF,
    ((USBD_PID & 0xFF00) >> 8),
    0x00, 0x00,     /* bcdDevice */
    0x01,           /* iManufacture */
    0x02,           /* iProduct */
    0x00,           /* iSerialNumber - no serial */
    0x01            /* bNumConfigurations */
};

/*!<USB Configure Descriptor */
uint8_t gu8ConfigDescriptor[] =
{
    LEN_CONFIG,     /* bLength */
    DESC_CONFIG,    /* bDescriptorType */
    /* wTotalLength */
    (LEN_CONFIG_AND_SUBORDINATE & 0x00FF),
    ((LEN_CONFIG_AND_SUBORDINATE & 0xFF00) >> 8),
    0x01,           /* bNumInterfaces */
    0x01,           /* bConfigurationValue */
    0x00,           /* iConfiguration */
    0x80 | (USBD_SELF_POWERED << 6) | (USBD_REMOTE_WAKEUP << 5),/* bmAttributes */
    USBD_MAX_POWER,         /* MaxPower */

    /* Interface Descriptor */
    LEN_INTERFACE,                     /* bLength */
    DESC_INTERFACE,                    /* bDescriptorType */
    0x00,                              /* bInterfaceNumber */
    0x00,                              /* bAlternateSetting */
    NUMBER_OF_EP,                      /* bNumEndpoints */
    0xFF,                              /* bInterfaceClass */
    0xFF,                              /* bInterfaceSubClass */
    0xFF,                              /* bInterfaceProtocol */
    0x00,                              /* iInterface */

    /* Endpoint Descriptor: EP7 bulk out. */
    LEN_ENDPOINT,                      /* bLength */
    DESC_ENDPOINT,                     /* bDescriptorType */
    (BULK_OUT_EP_NUM | EP_OUTPUT),     /* bEndpointAddress */
    EP_BULK,                           /* bmAttributes */
    EP2_MAX_PKT_SIZE & 0x00FF,         /* wMaxPacketSize */
    (EP2_MAX_PKT_SIZE & 0xFF00) >> 8,
    0x1                                /* bInterval */
};

/*!<USB Language String Descriptor */
uint8_t gu8StringLang[4] =
{
    4,              /* bLength */
    DESC_STRING,    /* bDescriptorType */
    0x09, 0x04
};

/*!<USB Vendor String Descriptor */
uint8_t gu8VendorStringDesc[] =
{
    16,
    DESC_STRING,
    'N', 0, 'u', 0, 'v', 0, 'o', 0, 't', 0, 'o', 0, 'n', 0
};

/*!<USB Product String Descriptor */
uint8_t gu8ProductStringDesc[] =
{
    32,
    DESC_STRING,
    'V', 0, 'e', 0, 'n', 0, 'd', 0, 'o', 0, 'r', 0, ' ', 0, 'L', 0, 'o', 0, 'o', 0, 'p', 0, 'b', 0, 'a', 0, 'c', 0, 'k', 0
};

/*!<USB BOS Descriptor */
uint8_t gu8BOSDescriptor[] =
{
    LEN_BOS,        /* bLength */
    DESC_BOS,       /* bDescriptorType */
    /* wTotalLength */
    0x0C & 0x00FF,
    ((0x0C & 0xFF00) >> 8),
    0x01,           /* bNumDeviceCaps */

    /* Device Capability */
    LEN_BOSCAP,     /* bLength */
    DESC_CAPABILITY,/* bDescriptorType */
    CAP_USB20_EXT,  /* bDevCapabilityType */
    0x02, 0x00, 0x00, 0x00  /* bmAttributes */
};

uint8_t *gpu8UsbString[4] =
{
    gu8StringLang,
    gu8VendorStringDesc,
    gu8ProductStringDesc,
    NULL,
};

uint8_t *gu8UsbHidReport[3] =
{
    NULL,
    NULL,
    NULL,
};

uint32_t gu32UsbHidReportLen[3] =
{
    0,
    0,
    0,
};

uint32_t gu32ConfigHidDescIdx[3] =
{
    (LEN_CONFIG+LEN_INTERFACE),
    0,
    0,
};

const S_USBD_INFO_T gsInfo =
{
    (uint8_t *)gu8DeviceDescriptor,
    (uint8_t *)gu8ConfigDescriptor,
    (uint8_t **)gpu8UsbString,
    (uint8_t **)gu8UsbHidReport,
    (uint8_t *)gu8BOSDescriptor,
    (uint32_t *)gu32UsbHidReportLen,
    (uint32_t *)gu32ConfigHidDescIdx
};

