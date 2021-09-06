/***************************************************************************//**
 * @file     vendor_lbk.c
 * @brief    M480 series USBD Vendor LBK device driver Sample file
 * @version  2.0.0
 *
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/

/*!<Includes */
#include <stdio.h>
#include <string.h>
#include "NuMicro.h"
#include "vendor_lbk.h"

/***************************************************/
uint8_t WINUSB_WCIDDescriptor[] = {
  ///////////////////////////////////////
  /// WCID descriptor
  ///////////////////////////////////////
  0x28, 0x00, 0x00, 0x00,                           /* dwLength */
  0x00, 0x01,                                       /* bcdVersion */
  0x04, 0x00,                                       /* wIndex */
  0x01,                                             /* bCount */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,         /* bReserved_7 */
  
  ///////////////////////////////////////
  /// WCID function descriptor
  ///////////////////////////////////////
  0x00,                                             /* bFirstInterfaceNumber */
  0x01,                                             /* bReserved */
  /* WINUSB */
  'W', 'I', 'N', 'U', 'S', 'B', 0x00, 0x00,         /* cCID_8 */
  /*  */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   /* cSubCID_8 */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,               /* bReserved_6 */
};
uint8_t WINUSB_IF0_WCIDProperties[142] = {
  ///////////////////////////////////////
  /// WCID property descriptor
  ///////////////////////////////////////
  0x8e, 0x00, 0x00, 0x00,                           /* dwLength */
  0x00, 0x01,                                       /* bcdVersion */
  0x05, 0x00,                                       /* wIndex */
  0x01, 0x00,                                       /* wCount */
  
  ///////////////////////////////////////
  /// registry propter descriptor
  ///////////////////////////////////////
  0x84, 0x00, 0x00, 0x00,                           /* dwSize */
  0x01, 0x00, 0x00, 0x00,                           /* dwPropertyDataType */
  0x28, 0x00,                                       /* wPropertyNameLength */
  /* DeviceInterfaceGUID */
  'D', 0x00, 'e', 0x00, 'v', 0x00, 'i', 0x00,       /* wcName_20 */
  'c', 0x00, 'e', 0x00, 'I', 0x00, 'n', 0x00,       /* wcName_20 */
  't', 0x00, 'e', 0x00, 'r', 0x00, 'f', 0x00,       /* wcName_20 */
  'a', 0x00, 'c', 0x00, 'e', 0x00, 'G', 0x00,       /* wcName_20 */
  'U', 0x00, 'I', 0x00, 'D', 0x00, 0x00, 0x00,      /* wcName_20 */
  0x4e, 0x00, 0x00, 0x00,                           /* dwPropertyDataLength */
  /* {1D4B2365-4749-48EA-B38A-7C6FDDDD7E26} */
  '{', 0x00, '1', 0x00, 'D', 0x00, '4', 0x00,       /* wcData_39 */
  'B', 0x00, '2', 0x00, '3', 0x00, '6', 0x00,       /* wcData_39 */
  '5', 0x00, '-', 0x00, '4', 0x00, '7', 0x00,       /* wcData_39 */
  '4', 0x00, '9', 0x00, '-', 0x00, '4', 0x00,       /* wcData_39 */
  '8', 0x00, 'E', 0x00, 'A', 0x00, '-', 0x00,       /* wcData_39 */
  'B', 0x00, '3', 0x00, '8', 0x00, 'A', 0x00,       /* wcData_39 */
  '-', 0x00, '7', 0x00, 'C', 0x00, '6', 0x00,       /* wcData_39 */
  'F', 0x00, 'D', 0x00, 'D', 0x00, 'D', 0x00,       /* wcData_39 */
  'D', 0x00, '7', 0x00, 'E', 0x00, '2', 0x00,       /* wcData_39 */
  '7', 0x00, '}', 0x00, 0x00, 0x00,                 /* wcData_39 */
};
/***************************************************/
typedef struct{
	uint8_t  bmRequestType;
	uint8_t  bRequest;
	uint16_t wValue;
	uint16_t wIndex;
	uint16_t wLength;
}ctrl_cmd_t;

extern const S_USBD_INFO_T *g_usbd_sInfo;
extern volatile uint8_t g_usbd_CtrlInZeroFlag;

volatile uint8_t g_u8EP2Ready = 0;      // EP2 for bulk-out

volatile uint8_t g_Ctrl_Buff[64];   // buffer for ctrl
uint8_t g_Bulk_Buff[EP2_BUF_LEN];   // buffer for bulk
/***************************************************/
void USBD_IRQHandler(void)
{
    uint32_t u32IntSts = USBD_GET_INT_FLAG();
    uint32_t u32State = USBD_GET_BUS_STATE();

//------------------------------------------------------------------
    if (u32IntSts & USBD_INTSTS_FLDET) {
        // Floating detect
        USBD_CLR_INT_FLAG(USBD_INTSTS_FLDET);

        if (USBD_IS_ATTACHED()) {
            /* USB Plug In */
            USBD_ENABLE_USB();
        } else {
            /* USB Un-plug */
            USBD_DISABLE_USB();
        }
    }

//------------------------------------------------------------------
    if (u32IntSts & USBD_INTSTS_BUS) {
        /* Clear event flag */
        USBD_CLR_INT_FLAG(USBD_INTSTS_BUS);

        if (u32State & USBD_STATE_USBRST) {
            /* Bus reset */
            USBD_ENABLE_USB();
            USBD_SwReset();
        }
        if (u32State & USBD_STATE_SUSPEND) {
            /* Enable USB but disable PHY */
            USBD_DISABLE_PHY();
        }
        if (u32State & USBD_STATE_RESUME) {
            /* Enable USB and enable PHY */
            USBD_ENABLE_USB();
        }
    }

//------------------------------------------------------------------
    if(u32IntSts & USBD_INTSTS_WAKEUP) {
        /* Clear event flag */
        USBD_CLR_INT_FLAG(USBD_INTSTS_WAKEUP);
    }

    if (u32IntSts & USBD_INTSTS_USB) {
        // USB event
        if (u32IntSts & USBD_INTSTS_SETUP) {
            // Setup packet
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_SETUP);

            /* Clear the data IN/OUT ready flag of control end-points */
            USBD_STOP_TRANSACTION(EP0);
            USBD_STOP_TRANSACTION(EP1);
            USBD_ProcessSetupPacket();
        }

        // EP events
        if (u32IntSts & USBD_INTSTS_EP0) {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP0);
            // control IN
            USBD_CtrlIn();
        }

        if (u32IntSts & USBD_INTSTS_EP1) {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP1);

            // control OUT
            USBD_CtrlOut();
        }

        if (u32IntSts & USBD_INTSTS_EP2) {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP2);

            /* Bulk-out data packet is ready */
            g_u8EP2Ready = 1;
        }
    }
}

/*--------------------------------------------------------------------------*/
/**
  * @brief  USBD Endpoint Config.
  * @param  None.
  * @retval None.
  */
void VendorLBK_Init(void)
{
    memset((void *)g_Ctrl_Buff, 0, sizeof(g_Ctrl_Buff));
    memset((void *)g_Bulk_Buff, 0, sizeof(g_Bulk_Buff));
    
    /* Init setup packet buffer */
    /* Buffer range for setup packet -> [0 ~ 0x7] */
    USBD->STBUFSEG = SETUP_BUF_BASE;

    /*****************************************************/
    /* EP0 ==> control IN endpoint, address 0 */
    USBD_CONFIG_EP(EP0, USBD_CFG_CSTALL | USBD_CFG_EPMODE_IN | 0);
    /* Buffer range for EP0 */
    USBD_SET_EP_BUF_ADDR(EP0, EP0_BUF_BASE);

    /* EP1 ==> control OUT endpoint, address 0 */
    USBD_CONFIG_EP(EP1, USBD_CFG_CSTALL | USBD_CFG_EPMODE_OUT | 0);
    /* Buffer range for EP1 */
    USBD_SET_EP_BUF_ADDR(EP1, EP1_BUF_BASE);

    /*****************************************************/
    /* EP2 ==> Bulk OUT endpoint, address 0x07 */
    USBD_CONFIG_EP(EP2, USBD_CFG_EPMODE_OUT | BULK_OUT_EP_NUM);
    /* Buffer range for EP5 */
    USBD_SET_EP_BUF_ADDR(EP2, EP2_BUF_BASE);

    /* trigger to send interrupt-in packet */
    USBD_SET_PAYLOAD_LEN(EP2, EP2_MAX_PKT_SIZE);
}

void VendorLBK_ClassRequest(void)
{
    uint8_t   buf[8];
    uint8_t   data_len;

    USBD_GetSetupPacket(buf);

    data_len = (buf[7]<<8) | buf[6];

    if (buf[0] & 0x80)   /* request data transfer direction */
    {
        // Device to host
        switch (buf[1])
        {
        case REQ_GET_DATA:
            if (data_len > 64)
                data_len = 64;
            //USBD_MemCopy((uint8_t *)(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)), (uint8_t *)&SendBuffer, g_SendLen);
            /* Data stage */
            USBD_PrepareCtrlIn((uint8_t *)g_Ctrl_Buff, data_len);
            /* Status stage */
            USBD_PrepareCtrlOut(0,0);
            break;

        default:
            /* Setup error, stall the device */
            USBD_SetStall(0);
            break;
        }
    }
    else
    {
        // Host to device
        switch (buf[1])
        {
        case REQ_SET_DATA:
            USBD_PrepareCtrlOut((uint8_t *)g_Ctrl_Buff, buf[6]);

            /* Request Type = INPUT */
            USBD_SET_DATA1(EP1);
            USBD_SET_PAYLOAD_LEN(EP1, data_len);
            /* Status stage */
            USBD_PrepareCtrlIn(0, 0);
            break;

        default:
            // Stall
            /* Setup error, stall the device */
            USBD_SetStall(0);
            break;
        }
    }
}

void VendorLBK_VendorRequest(void)
{
    uint8_t   buf[8];
    uint8_t   data_len;
    uint16_t wIndex;
    uint32_t u32Len;
    
    USBD_GetSetupPacket(buf);
    
    data_len = (buf[7]<<8) | buf[6];
    wIndex = (buf[5] << 8) | buf[4];
    
    if (buf[0] & 0x80) {
        // Device to host
        switch (buf[1]) {
        case WCID_VENDOR_CODE:
            if (wIndex == 0x0004) {
                u32Len = WINUSB_WCIDDescriptor[0];
                if (u32Len > data_len)            
                    u32Len = data_len;
                
                if ((u32Len % 64) == 0ul) {
                    g_usbd_CtrlInZeroFlag = (uint8_t)1ul;
                }
                
                USBD_PrepareCtrlIn(WINUSB_WCIDDescriptor, u32Len);
                
                /* Status stage */
                USBD_PrepareCtrlOut(0,0);
                
            } else if (wIndex == 0x0005) {
                u32Len = WINUSB_IF0_WCIDProperties[0];
                if (u32Len > data_len)            
                    u32Len = data_len;
                
                if ((u32Len % 64) == 0ul) {
                    g_usbd_CtrlInZeroFlag = (uint8_t)1ul;
                }
                
                USBD_PrepareCtrlIn((uint8_t *)WINUSB_IF0_WCIDProperties, u32Len);
                
                /* Status stage */
                USBD_PrepareCtrlOut(0,0);
            }
        break;
        default:
            // Stall
            /* Setup error, stall the device */
            USBD_SetStall(0);
            break;
        }
    } else {
        // Host to device
        switch (buf[1]) {
        default:
            // Stall
            /* Setup error, stall the device */
            USBD_SetStall(0);
            break;
        }
    }
}

static void dump_raw_hex(uint8_t *buf, uint32_t len)
{
    int nIdx, i;

    nIdx = 0;
    while (len > 0) {
        printf("0x%04X  ", nIdx);
        for (i = 0; (i < 16) && (len > 0); i++) {
            printf("%02x ", buf[nIdx + i]);
            len--;
        }
        nIdx += 16;
        printf("\n");
    }
    printf("\n");
}

void VendorLBK_ProcessData(void)
{
    uint32_t data_len, i;
    
    if (g_u8EP2Ready) {
        g_u8EP2Ready = 0;
        
        data_len = USBD_GET_PAYLOAD_LEN(EP2);
        if (data_len > EP2_MAX_PKT_SIZE) {
            printf("Error! EP2 data overrun!\n");
            data_len = EP2_MAX_PKT_SIZE;
        }
        
        /* Read bulk-out packet from USBD SRAM to g_Bulk_Buff[] */
        for (i = 0; i < data_len; i++) {
            g_Bulk_Buff[i] = inpb(USBD_BUF_BASE + EP2_BUF_BASE + i);
        }
        
        printf("[BULK-OUT]\r\n");
        dump_raw_hex(g_Bulk_Buff, data_len);

        USBD_SET_PAYLOAD_LEN(EP2, 0);
    }
}
