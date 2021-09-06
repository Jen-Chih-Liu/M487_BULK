/*!<Includes */
#include "NuMicro.h"
#include "vendor_lbk.h"

/*----------------------------------------------------------------------------*/
/*!<USB Device Descriptor */
uint8_t gu8DeviceDescriptor[] = {
  ///////////////////////////////////////
  /// device descriptor
  ///////////////////////////////////////
  0x12,                                             /* bLength */
  DESC_DEVICE,                                      /* bDescriptorType */
  0x00, 0x02,                                       /* bcdUSB */
  0x00,                                             /* bDeviceClass */
  0x00,                                             /* bDeviceSubClass */
  0x00,                                             /* bDeviceProtocol */
  0x40,                                             /* bMaxPacketSize */
  0x16, 0x04,                                       /* idVendor */
  0x22, 0xff,                                       /* idProduct */
  0x00, 0x01,                                       /* bcdDevice */
  0x01,                                             /* iManufacturer */
  0x02,                                             /* iProduct */
  0x03,                                             /* iSerial */
  0x01,                                             /* bNumConfigurations */
};

/*!<USB Configure Descriptor */
uint8_t gu8ConfigDescriptor[] = {
  ///////////////////////////////////////
  /// config descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  DESC_CONFIG,                                      /* bDescriptorType */
  0x19, 0x00,                                       /* wTotalLength */
  0x01,                                             /* bNumInterfaces */
  0x01,                                             /* bConfigurationValue */
  0x00,                                             /* iConfiguration */
  0x80,                                             /* bmAttributes */
  0x64,                                             /* bMaxPower */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  DESC_INTERFACE,                                   /* bDescriptorType */
  0x00,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x01,                                             /* bNumEndpoints */
  0xff,                                             /* bInterfaceClass */
  0xff,                                             /* bInterfaceSubClass */
  0x00,                                             /* bInterfaceProtocol */
  0x00,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  DESC_ENDPOINT,                                    /* bDescriptorType */
  0x02,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x40, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
};

/*!<USB Language String Descriptor */
uint8_t gu8StringLang[4] = {
  0x04,                                         /* bLength */
  DESC_STRING,                                  /* bDescriptorType */
  0x09, 0x04,                                   /* wLangID0 */
};

/*!<USB Vendor String Descriptor */
uint8_t gu8VendorStringDesc[] = {
  0x10,                                             /* bLength */
  DESC_STRING,                                      /* bDescriptorType */
  'N', 0x00,                                        /* wcChar0 */
  'U', 0x00,                                        /* wcChar1 */
  'V', 0x00,                                        /* wcChar2 */
  'O', 0x00,                                        /* wcChar3 */
  'T', 0x00,                                        /* wcChar4 */
  'O', 0x00,                                        /* wcChar5 */
  'N', 0x00,                                        /* wcChar6 */
};

/*!<USB Product String Descriptor */
uint8_t gu8ProductStringDesc[] = {
  0x14,                                             /* bLength */
  DESC_STRING,                                      /* bDescriptorType */
  'M', 0x00,                                        /* wcChar0 */
  '4', 0x00,                                        /* wcChar1 */
  '8', 0x00,                                        /* wcChar2 */
  '0', 0x00,                                        /* wcChar3 */
  ' ', 0x00,                                        /* wcChar4 */
  'B', 0x00,                                        /* wcChar5 */
  'U', 0x00,                                        /* wcChar6 */
  'L', 0x00,                                        /* wcChar7 */
  'K', 0x00,                                        /* wcChar8 */
};

uint8_t gu8SerialStringDesc[] = {
  0x0e,                                             /* bLength */
  DESC_STRING,                                      /* bDescriptorType */
  'v', 0x00,                                        /* wcChar0 */
  '1', 0x00,                                        /* wcChar1 */
  '2', 0x00,                                        /* wcChar2 */
  '3', 0x00,                                        /* wcChar3 */
  '4', 0x00,                                        /* wcChar4 */
  '5', 0x00,                                        /* wcChar5 */
};

uint8_t gu8WinUSBStringDesc[] = {
  0x22,                                             /* bLength */
  DESC_STRING,                                      /* bDescriptorType */
  'M', 0x00,                                        /* wcChar0 */
  '4', 0x00,                                        /* wcChar1 */
  '8', 0x00,                                        /* wcChar2 */
  '0', 0x00,                                        /* wcChar3 */
  ' ', 0x00,                                        /* wcChar4 */
  'W', 0x00,                                        /* wcChar5 */
  'i', 0x00,                                        /* wcChar6 */
  'n', 0x00,                                        /* wcChar7 */
  'U', 0x00,                                        /* wcChar8 */
  'S', 0x00,                                        /* wcChar9 */
  'B', 0x00,                                        /* wcChar10 */
  ' ', 0x00,                                        /* wcChar11 */
  'B', 0x00,                                        /* wcChar12 */
  'U', 0x00,                                        /* wcChar13 */
  'L', 0x00,                                        /* wcChar14 */
  'K', 0x00,                                        /* wcChar15 */
};

// Define WCID os string descriptor 
uint8_t  gu8OsStringDesc[] = {
  ///////////////////////////////////////
  /// MS OS string descriptor
  ///////////////////////////////////////
  0x12,                                             /* bLength */
  DESC_STRING,                                      /* bDescriptorType */
  /* MSFT100 */
  'M', 0x00, 'S', 0x00, 'F', 0x00, 'T', 0x00,       /* wcChar_7 */
  '1', 0x00, '0', 0x00, '0', 0x00,                  /* wcChar_7 */
  WCID_VENDOR_CODE,                                 /* bVendorCode */
  0x00,                                             /* bReserved */
};

/*!<USB BOS Descriptor */
uint8_t gu8BOSDescriptor[] = {
    LEN_BOS,                /* bLength */
    DESC_BOS,               /* bDescriptorType */
    0x0C & 0x00FF,          /* wTotalLength */
    ((0x0C & 0xFF00) >> 8),
    0x01,                   /* bNumDeviceCaps */

    /* Device Capability */
    LEN_BOSCAP,             /* bLength */
    DESC_CAPABILITY,        /* bDescriptorType */
    CAP_USB20_EXT,          /* bDevCapabilityType */
    0x02, 0x00, 0x00, 0x00  /* bmAttributes */
};

uint8_t *gpu8UsbString[6] = {
    gu8StringLang,
    gu8VendorStringDesc,
    gu8ProductStringDesc,
    gu8SerialStringDesc,
    gu8OsStringDesc,
    gu8WinUSBStringDesc,
};

const S_USBD_INFO_T gsInfo = {
    (uint8_t *)gu8DeviceDescriptor,
    (uint8_t *)gu8ConfigDescriptor,
    (uint8_t **)gpu8UsbString,
    (uint8_t **)NULL,
    (uint8_t *)gu8BOSDescriptor,
    (uint32_t *)NULL,
    (uint32_t *)NULL
};

