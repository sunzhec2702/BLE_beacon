/******************************************************************************

 @file  simpleBLEBroadcaster.c

 @brief This file contains the Simple BLE Broadcaster sample application for
        use with the CC2540 Bluetooth Low Energy Protocol Stack.

 Group: WCS, BTS
 Target Device: CC2540, CC2541

 ******************************************************************************
 
 Copyright (c) 2011-2016, Texas Instruments Incorporated
 All rights reserved.

 IMPORTANT: Your use of this Software is limited to those specific rights
 granted under the terms of a software license agreement between the user
 who downloaded the software, his/her employer (which must be your employer)
 and Texas Instruments Incorporated (the "License"). You may not use this
 Software unless you agree to abide by the terms of the License. The License
 limits your use, and you acknowledge, that the Software may not be modified,
 copied or distributed unless embedded on a Texas Instruments microcontroller
 or used solely and exclusively in conjunction with a Texas Instruments radio
 frequency transceiver, which is integrated into your product. Other than for
 the foregoing purpose, you may not use, reproduce, copy, prepare derivative
 works of, modify, distribute, perform, display or sell this Software and/or
 its documentation for any purpose.

 YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
 PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
 INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE,
 NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
 TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
 NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
 LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
 INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
 OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
 OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
 (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

 Should you have any questions regarding your right to use this Software,
 contact Texas Instruments Incorporated at www.TI.com.

 ******************************************************************************
 Release Name: ble_sdk_1.4.2.2
 Release Date: 2016-06-09 06:57:10
 *****************************************************************************/

/*********************************************************************
 * INCLUDES
 */

#include "bcomdef.h"
#include "OSAL.h"
#include "OSAL_PwrMgr.h"

#include "OnBoard.h"
#include "hal_adc.h"
#include "hal_led.h"
#include "hal_key.h"
#include "hal_lcd.h"

#include "hci.h"
#include "gap.h"

#include "devinfoservice.h"
#include "broadcaster.h"

#include "simpleBLEBroadcaster.h"
#include "npi.h"
/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * CONSTANTS
 */

// What is the advertising interval when device is discoverable (units of 625us, 160=100ms)
#define DEFAULT_ADVERTISING_INTERVAL          160

// Company Identifier: Texas Instruments Inc. (13)
#define TI_COMPANY_ID                         0x000D

// Length of bd addr as a string
#define B_ADDR_STR_LEN                        15

/*********************************************************************
 * STATIC FUNCTIONS
 */
static void NpiSerialCallback( uint8 port, uint8 events );
/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
 * GLOBAL VARIABLES
 */

/*********************************************************************
 * EXTERNAL VARIABLES
 */

/*********************************************************************
 * EXTERNAL FUNCTIONS
 */

/*********************************************************************
 * LOCAL VARIABLES
 */
static uint8 simpleBLEBroadcaster_TaskID;   // Task ID for internal task/event processing

// GAP - SCAN RSP data (max size = 31 bytes)
static uint8 scanRspData[] =
{
  // complete name
  0x0A,   // length of this data
  GAP_ADTYPE_LOCAL_NAME_COMPLETE,
  0x44,
  0x61,
  0x72,
  0x72,
  0x65,
  0x6e,
  0x42,
  0x4c,
  0x45,
  0x02,   // length of this data
  GAP_ADTYPE_POWER_LEVEL,
  0       // 0dBm  
};

// GAP - Advertisement data (max size = 31 bytes, though this is
// best kept short to conserve power while advertisting)
static uint8 advertData[] = 
{ 
  // Flags; this sets the device to use limited discoverable
  // mode (advertises for 30 seconds at a time) instead of general
  // discoverable mode (advertises indefinitely)
  0x02,   // length of this data
  GAP_ADTYPE_FLAGS,
  GAP_ADTYPE_FLAGS_BREDR_NOT_SUPPORTED,

  // three-byte broadcast of the data "1 2 3"
  0x1A,   // length of this data including the data type byte
  GAP_ADTYPE_MANUFACTURER_SPECIFIC,      // manufacturer specific advertisement data type
  0x4C,
  0x00,
  0x02,
  0x15,
  0xE2, 0xC5, 0x6D, 0xB5, 0xDF, 0xFB, 0x48, 0xD2, 0xB0, 0x60, 0xD0, 0xF5, 0xA7,
  0x10, 0x96, 0xE0,
  0x00, 0x01,
  0x00, 0x02,
  0xCD
};

/*********************************************************************
 * LOCAL FUNCTIONS
 */
static void simpleBLEBroadcaster_ProcessOSALMsg( osal_event_hdr_t *pMsg );
static void peripheralStateNotificationCB( gaprole_States_t newState );

#if defined( HAL_BOARD_CC2541YM_REV1 )
static void simpleBLEBroadcaster_HandleKeys( uint8 shift, uint8 keys );
#endif

#if (defined HAL_LCD) && (HAL_LCD == TRUE) 
static char *bdAddr2Str ( uint8 *pAddr );
#endif // (defined HAL_LCD) && (HAL_LCD == TRUE) 

/*********************************************************************
 * PROFILE CALLBACKS
 */

// GAP Role Callbacks
static gapRolesCBs_t simpleBLEBroadcaster_BroadcasterCBs =
{
  peripheralStateNotificationCB,  // Profile State Change Callbacks
  NULL                            // When a valid RSSI is read from controller (not used by application)
};

/*********************************************************************
 * PUBLIC FUNCTIONS
 */

/*********************************************************************
 * @fn      SimpleBLEBroadcaster_Init
 *
 * @brief   Initialization function for the Simple BLE Broadcaster App
 *          Task. This is called during initialization and should contain
 *          any application specific initialization (ie. hardware
 *          initialization/setup, table initialization, power up
 *          notificaiton ... ).
 *
 * @param   task_id - the ID assigned by OSAL.  This ID should be
 *                    used to send messages and set timers.
 *
 * @return  none
 */
void SimpleBLEBroadcaster_Init( uint8 task_id )
{
  simpleBLEBroadcaster_TaskID = task_id;
  // UART Test.
  {
    NPI_InitTransport(NpiSerialCallback);
    NPI_WriteTransport("SimpleBLETest_Init\r\n", 20);
    NPI_PrintString("SimpleBLETest_Init2\r\n");  
    NPI_PrintValue("AmoMcu 1 = ", 168, 10);
    NPI_PrintString("\r\n");  
    NPI_PrintValue("AmoMcu 2 = 0x", 0x88, 16);
    NPI_PrintString("\r\n");  
  }
  
  // Setup the GAP Broadcaster Role Profile
  {
    // Darren : Directly start the advertising.
    uint8 initial_advertising_enable = TRUE;

    // By setting this to zero, the device will go into the waiting state after
    // being discoverable for 30.72 second, and will not being advertising again
    // until the enabler is set back to TRUE
    uint16 gapRole_AdvertOffTime = 0;
      
    // Darren: modify this to NON_CONN.
    // uint8 advType = GAP_ADTYPE_ADV_NONCONN_IND;   // use non-connectable advertisements
    uint8 advType = GAP_ADTYPE_ADV_SCAN_IND; // use scannable unidirected advertisements

    // Set the GAP Role Parameters
    GAPRole_SetParameter( GAPROLE_ADVERT_ENABLED, sizeof( uint8 ), &initial_advertising_enable );
    GAPRole_SetParameter( GAPROLE_ADVERT_OFF_TIME, sizeof( uint16 ), &gapRole_AdvertOffTime );
    
    GAPRole_SetParameter( GAPROLE_SCAN_RSP_DATA, sizeof ( scanRspData ), scanRspData );
    GAPRole_SetParameter( GAPROLE_ADVERT_DATA, sizeof( advertData ), advertData );

    GAPRole_SetParameter( GAPROLE_ADV_EVENT_TYPE, sizeof( uint8 ), &advType );
  }

  // Set advertising interval
  {
    uint16 advInt = DEFAULT_ADVERTISING_INTERVAL;

    GAP_SetParamValue( TGAP_LIM_DISC_ADV_INT_MIN, advInt );
    GAP_SetParamValue( TGAP_LIM_DISC_ADV_INT_MAX, advInt );
    GAP_SetParamValue( TGAP_GEN_DISC_ADV_INT_MIN, advInt );
    GAP_SetParamValue( TGAP_GEN_DISC_ADV_INT_MAX, advInt );
  }

  HalLedSet( (HAL_LED_1 | HAL_LED_2 | HAL_LED_3), HAL_LED_MODE_OFF );
  RegisterForKeys( simpleBLEBroadcaster_TaskID );
 
#if (defined HAL_LCD) && (HAL_LCD == TRUE)  

  HalLcdWriteString( "BLE Broadcaster", HAL_LCD_LINE_1 );
  
#endif // (defined HAL_LCD) && (HAL_LCD == TRUE)  
  
  // Setup a delayed profile startup
  osal_set_event( simpleBLEBroadcaster_TaskID, SBP_START_DEVICE_EVT );
}

/*********************************************************************
 * @fn      SimpleBLEBroadcaster_ProcessEvent
 *
 * @brief   Simple BLE Broadcaster Application Task event processor. This
 *          function is called to process all events for the task. Events
 *          include timers, messages and any other user defined events.
 *
 * @param   task_id  - The OSAL assigned task ID.
 * @param   events - events to process.  This is a bit map and can
 *                   contain more than one event.
 *
 * @return  events not processed
 */
uint16 SimpleBLEBroadcaster_ProcessEvent( uint8 task_id, uint16 events )
{
  
  VOID task_id; // OSAL required parameter that isn't used in this function
  
  if ( events & SYS_EVENT_MSG )
  {
    uint8 *pMsg;

    if ( (pMsg = osal_msg_receive( simpleBLEBroadcaster_TaskID )) != NULL )
    {
      simpleBLEBroadcaster_ProcessOSALMsg( (osal_event_hdr_t *)pMsg );

      // Release the OSAL message
      VOID osal_msg_deallocate( pMsg );
    }

    // return unprocessed events
    return (events ^ SYS_EVENT_MSG);
  }

  if ( events & SBP_START_DEVICE_EVT )
  {
    // Start the Device
    VOID GAPRole_StartDevice( &simpleBLEBroadcaster_BroadcasterCBs );
    
    return ( events ^ SBP_START_DEVICE_EVT );
  }
  
  // Discard unknown events
  return 0;
}

/*********************************************************************
 * @fn      simpleBLEBroadcaster_ProcessOSALMsg
 *
 * @brief   Process an incoming task message.
 *
 * @param   pMsg - message to process
 *
 * @return  none
 */
static void simpleBLEBroadcaster_ProcessOSALMsg( osal_event_hdr_t *pMsg )
{
  HalLedSet(HAL_LED_2, HAL_LED_MODE_BLINK );
  NPI_PrintString("ProcessOSALMsg\r\n");
  switch ( pMsg->event )
  {
  #if defined( HAL_BOARD_CC2541YM_REV1 )
    case KEY_CHANGE:
      NPI_PrintString("ProcessOSALMsg_Key_Change\r\n");
      simpleBLEBroadcaster_HandleKeys( ((keyChange_t *)pMsg)->state, ((keyChange_t *)pMsg)->keys );
      break;
  #endif // HAL_BOARD_CC2541YM_REV1
      
  default:
    // do nothing
    break;
  }
}

#if defined( HAL_BOARD_CC2541YM_REV1 )
/*********************************************************************
 * @fn      simpleBLEBroadcaster_HandleKeys
 *
 * @brief   Handles all key events for this device.
 *
 * @param   shift - true if in shift/alt.
 * @param   keys - bit field for key events. Valid entries:
 *                 HAL_KEY_SW_2
 *                 HAL_KEY_SW_1
 *
 * @return  none
 */
static void simpleBLEBroadcaster_HandleKeys( uint8 shift, uint8 keys )
{
  VOID shift;  // Intentionally unreferenced parameter
  NPI_PrintValue("shift = ", shift, 10);
  NPI_PrintValue("keys = ", keys, 10);
  if ( keys & HAL_KEY_SW_1 )
  {
    NPI_PrintString("KEY_SW_1 is pressed\r\n");
    advertData[26] += 1;
    NPI_PrintValue("value = ", advertData[26], 10);
    GAPRole_SetParameter( GAPROLE_ADVERT_DATA, sizeof( advertData ), advertData );
    //advertData[6]++;
    //GAPRole_SetParameter( GAPROLE_ADVERT_DATA, sizeof( advertData ), advertData );
  }
}
#endif // HAL_BOARD_CC2541YM_REV1

/*********************************************************************
 * @fn      peripheralStateNotificationCB
 *
 * @brief   Notification from the profile of a state change.
 *
 * @param   newState - new state
 *
 * @return  none
 */
static void peripheralStateNotificationCB( gaprole_States_t newState )
{
  switch ( newState )
  {
    case GAPROLE_STARTED:
      {    
        uint8 ownAddress[B_ADDR_LEN];
        
        GAPRole_GetParameter(GAPROLE_BD_ADDR, ownAddress);
    
        #if (defined HAL_LCD) && (HAL_LCD == TRUE)
          // Display device address 
          HalLcdWriteString( bdAddr2Str( ownAddress ),  HAL_LCD_LINE_2 );
          HalLcdWriteString( "Initialized",  HAL_LCD_LINE_3 );
        #endif // (defined HAL_LCD) && (HAL_LCD == TRUE)    
      }
      break;
      
    case GAPROLE_ADVERTISING:
      {
        #if (defined HAL_LCD) && (HAL_LCD == TRUE)
          HalLcdWriteString( "Advertising",  HAL_LCD_LINE_3 );
        #endif // (defined HAL_LCD) && (HAL_LCD == TRUE)            
      }
      break;

    case GAPROLE_WAITING:
      {
        #if (defined HAL_LCD) && (HAL_LCD == TRUE)
          HalLcdWriteString( "Waiting",  HAL_LCD_LINE_3 );
        #endif // (defined HAL_LCD) && (HAL_LCD == TRUE)            
      }
      break;          

    case GAPROLE_ERROR:
      {
        #if (defined HAL_LCD) && (HAL_LCD == TRUE)
          HalLcdWriteString( "Error",  HAL_LCD_LINE_3 );
        #endif // (defined HAL_LCD) && (HAL_LCD == TRUE)            
      }
      break;      
      
    default:
      {
        #if (defined HAL_LCD) && (HAL_LCD == TRUE)
          HalLcdWriteString( "",  HAL_LCD_LINE_3 );
        #endif // (defined HAL_LCD) && (HAL_LCD == TRUE)     
      }        
      break; 
  }
}

#if (defined HAL_LCD) && (HAL_LCD == TRUE)
/*********************************************************************
 * @fn      bdAddr2Str
 *
 * @brief   Convert Bluetooth address to string. Only needed when
 *          LCD display is used.
 *
 * @return  none
 */
char *bdAddr2Str( uint8 *pAddr )
{
  uint8       i;
  char        hex[] = "0123456789ABCDEF";
  static char str[B_ADDR_STR_LEN];
  char        *pStr = str;
  
  *pStr++ = '0';
  *pStr++ = 'x';
  
  // Start from end of addr
  pAddr += B_ADDR_LEN;
  
  for ( i = B_ADDR_LEN; i > 0; i-- )
  {
    *pStr++ = hex[*--pAddr >> 4];
    *pStr++ = hex[*pAddr & 0x0F];
  }
  
  *pStr = 0;
  
  return str;
}
#endif // (defined HAL_LCD) && (HAL_LCD == TRUE) 


// ´®¿Ú»Øµ÷º¯Êı£¬ ÏÂÃæ°Ñ¸Ã»Øµ÷º¯ÊıÀïÊµÏÖµÄ¹¦ÄÜ½²½âÒ»ÏÂ
/*
1, Ë¼Â·:  µ±´®¿ÚÊÕµ½Êı¾İºó£¬¾Í»áÂíÉÏµ÷ÓÃÒÔÏÂ»Øµ÷º¯Êı£¬ÔÚÊµ¼Ê²âÊÔÖĞ·¢ÏÖ£¬´Ë»Øµ÷
º¯Êıµ÷ÓÃÆµ·±£¬ Èç¹ûÄã²»Ö´ĞĞNPI_ReadTransportº¯Êı½øĞĞ¶ÁÈ¡£¬ ÄÇÃ´Õâ¸ö»Øµ÷º¯Êı¾Í»á
Æµ·±µØ±»Ö´ĞĞ£¬µ«ÊÇ£¬ÄãÍ¨¹ı´®¿Ú·¢ËÍÒ»¶ÎÊı¾İ£¬ Äã±¾ÒâÊÇÏë´¦ÀíÕâÒ»ÍêÕûÒ»¶ÎµÄÊı¾İ£¬ËùÒÔ£¬
ÎÒÃÇÔÚÏÂÃæÒıÈëÁËÊ±¼äµÄ´¦Àí·½·¨£¬ Ò²¼´½ÓÊÕµÄÊı¾İ¹»¶à»òÕß³¬Ê±£¬¾Í¶ÁÈ¡Ò»´ÎÊı¾İ£¬ 
È»ºó¸ù¾İµ±Ç°µÄ×´Ì¬¾ö¶¨Ö´ĞĞ£¬Èç¹ûÃ»ÓĞÁ¬½ÓÉÏ£¬¾Í°ÑËùÓĞÊı¾İµ±×öATÃüÁî´¦Àí£¬ Èç¹ûÁ¬½Ó
ÉÏÁË£¬¾Í°ÑÊı¾İËÍµ½¶Ô¶Ë¡£  ---------------amomcu   2014.08.17
*/
static void NpiSerialCallback( uint8 port, uint8 events )
{
    (void)port;//¼Ó¸ö (void)£¬ÊÇÎ´ÁË±ÜÃâ±àÒë¸æ¾¯£¬Ã÷È·¸æËß»º³åÇø²»ÓÃÀí»áÕâ¸ö±äÁ¿
    if (events & (HAL_UART_RX_TIMEOUT | HAL_UART_RX_FULL))   //´®¿ÚÓĞÊı¾İ
    {
        uint8 numBytes = 0;

        numBytes = NPI_RxBufLen();           //¶Á³ö´®¿Ú»º³åÇøÓĞ¶àÉÙ×Ö½Ú
        
        if(numBytes == 0)
        {
            return;
        }
        else
        {
            //ÉêÇë»º³åÇøbuffer
            uint8 *buffer = osal_mem_alloc(numBytes);
            if(buffer)
            {
                //¶ÁÈ¡¶ÁÈ¡´®¿Ú»º³åÇøÊı¾İ£¬ÊÍ·Å´®¿ÚÊı¾İ   
                NPI_ReadTransport(buffer,numBytes);   

                //°ÑÊÕµ½µÄÊı¾İ·¢ËÍµ½´®¿Ú-ÊµÏÖ»Ø»· 
                NPI_WriteTransport(buffer, numBytes);  

                //ÊÍ·ÅÉêÇëµÄ»º³åÇø
                osal_mem_free(buffer);
            }
        }
    }
}


/*********************************************************************
*********************************************************************/
