/***************************************************************************//**
 * @file     vendor_lbk.h
 * @brief    M480 series USBD Vendor LBK driver header file
 * @version  2.0.0
 *
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef __VENDOR_LBK_H_
#define __VENDOR_LBK_H_

/* Define the vendor id and product id */
#define USBD_VID            0x0416
#define USBD_PID            0xff20

/*-------------------------------------------------------------*/
/* Define Endpoints */
#define NUMBER_OF_EP        1

#define EP0_MAX_PKT_SIZE    64
#define EP1_MAX_PKT_SIZE    EP0_MAX_PKT_SIZE

#define EP2_MAX_PKT_SIZE    64

#define SETUP_BUF_BASE      0
#define SETUP_BUF_LEN       8
#define EP0_BUF_BASE        64
#define EP0_BUF_LEN         EP0_MAX_PKT_SIZE
#define EP1_BUF_BASE        (EP0_BUF_BASE + EP0_BUF_LEN)
#define EP1_BUF_LEN         EP1_MAX_PKT_SIZE
#define EP2_BUF_BASE        (EP1_BUF_BASE + EP1_BUF_LEN)
#define EP2_BUF_LEN         EP2_MAX_PKT_SIZE

/* Define the EP number */
#define BULK_OUT_EP_NUM       0x02

/* Define Descriptor information */
#define USBD_SELF_POWERED               0
#define USBD_REMOTE_WAKEUP              0
#define USBD_MAX_POWER                  50  /* The unit is in 2mA. ex: 50 * 2mA = 100mA */

#define LEN_CONFIG_AND_SUBORDINATE      (LEN_CONFIG + LEN_INTERFACE + LEN_ENDPOINT)


/*-------------------------------------------------------------*/
/* Vendor LBK device vendor commands */
#define REQ_SET_DATA        0x01
#define REQ_GET_DATA        0x12

/*-------------------------------------------------------------*/

/*-------------------------------------------------------------*/
void VendorLBK_Init(void);
void VendorLBK_ClassRequest(void);
void VendorLBK_ProcessData(void);

uint8_t* VendorLBK_getDisplayPtr(void);

#endif  /* __VENDOR_LBK_H_ */

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/
