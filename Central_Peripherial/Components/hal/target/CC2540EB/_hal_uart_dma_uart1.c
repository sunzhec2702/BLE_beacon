/******************************************************************************

 @file  _hal_uart_dma.c

 @brief This file contains the interface to the H/W UART driver by DMA.
        
        A known defect is that when flow control is enabled, the function
        HalUARTPollTxTrigDMA() can prematurely invoke
        HAL_DMA_MAN_TRIGGER(HAL_DMA_CH_TX) and clobber that last byte of one
        txBuf[] block transfer with the first byte of the next txBuf[] block
        transfer.  Additionally, Tx can become permanently stalled during heavy
        use and/or simultaeous heavy radio traffic when using DMA for the Tx
        and hardware flow control.

 Group: WCS, BTS
 Target Device: CC2540, CC2541

 ******************************************************************************
 
 Copyright (c) 2006-2016, Texas Instruments Incorporated
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
 PROVIDED “AS IS? WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
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
 Release Date: 2016-06-09 06:57:09
 *****************************************************************************/

/* ------------------------------------------------------------------------------------------------
 *                                          Includes
 * ------------------------------------------------------------------------------------------------
 */

#include <string.h>

#include "hal_assert.h"
#include "hal_board.h"
#include "hal_defs.h"
#include "hal_dma.h"
#include "hal_mcu.h"
#include "hal_types.h"
#include "hal_uart.h"

/* ------------------------------------------------------------------------------------------------
 *                                           Constants
 * ------------------------------------------------------------------------------------------------
 */

// UxCSR_UART1 - USART Control and Status Register.
#define CSR_MODE_UART1                   0x80
#define CSR_RE_UART1                     0x40
#define CSR_SLAVE_UART1                  0x20
#define CSR_FE_UART1                     0x10
#define CSR_ERR_UART1                    0x08
#define CSR_RX_BYTE_UART1                0x04
#define CSR_TX_BYTE_UART1                0x02
#define CSR_ACTIVE_UART1                 0x01

// UxUCR_UART1 - USART UART Control Register.
#define UCR_FLUSH_UART1                  0x80
#define UCR_FLOW_UART1                   0x40
#define UCR_D9_UART1                     0x20
#define UCR_BIT9_UART1                   0x10
#define UCR_PARITY_UART1                 0x08
#define UCR_SPB_UART1                    0x04
#define UCR_STOP_UART1                   0x02
#define UCR_START_UART1                  0x01

#define UTX0IE_UART1                     0x04
#define UTX1IE_UART1                     0x08

#define P2DIR_PRIPO_UART1                0xC0

#define HAL_DMA_U0DBUF_UART1             0x70C1
#define HAL_DMA_U1DBUF_UART1             0x70F9

#undef  UxCSR_UART1
#undef  UxUCR_UART1
#undef  UxDBUF_UART1
#undef  UxBAUD_UART1
#undef  UxGCR_UART1
#undef UTXxIE_UART1
#undef UTXxIF_UART1

#define UxCSR_UART1                      U1CSR
#define UxUCR_UART1                      U1UCR
#define UxDBUF_UART1                     U1DBUF
#define UxBAUD_UART1                     U1BAUD
#define UxGCR_UART1                      U1GCR
#define UTXxIE_UART1                     UTX1IE_UART1
#define UTXxIF_UART1                     UTX1IF

#undef  PxSEL_UART1
#undef  HAL_UART_PERCFG_BIT_UART1
#undef  HAL_UART_PRIPO_UART1
#undef  HAL_UART_Px_CTS_UART1
#undef  HAL_UART_Px_RTS_UART1
#undef  HAL_UART_Px_SEL_UART1

#define PxSEL_UART1                      P1SEL
#define HAL_UART_PERCFG_BIT_UART1        0x02         // USART1 on P1, Alt-2; so set this bit.
#define HAL_UART_PRIPO_UART1             0x40         // USART1 priority over UART0.
#define HAL_UART_Px_CTS_UART1            0x10         // Peripheral I/O Select for CTS flow control.
#define HAL_UART_Px_RTS_UART1            0x20         // Peripheral I/O Select for RTS must be manual.
#define HAL_UART_Px_SEL_UART1            0xC0         // Peripheral I/O Select for Rx/Tx.

#undef  DMA_PAD_UART1
#undef  DMA_UxDBUF_UART1
#undef  DMATRIG_RX_UART1
#undef  DMATRIG_TX_UART1

#define DMA_PAD_UART1                    U1BAUD
#define DMA_UxDBUF_UART1                 HAL_DMA_U1DBUF_UART1
#define DMATRIG_RX_UART1                 HAL_DMA_TRIG_URX1
#define DMATRIG_TX_UART1                 HAL_DMA_TRIG_UTX1

#undef  PxDIR_UART1
#undef  PxIEN_UART1
#undef  PxIFG_UART1
#undef  PxIF_UART1
#undef  PICTL_BIT_UART1
#undef  IENx_UART1
#undef  IEN_BIT_UART1

#define PxDIR_UART1                      P1DIR
#define PxIEN_UART1                      P1IEN
#define PxIFG_UART1                      P1IFG
#define PxIF_UART1                      P1IF
#define DMA_RDYIn_UART1                  P1_4
#define DMA_RDYOut_UART1                 P1_5
#define DMA_RDYIn_UART1_BIT              BV(4)        // Same as the I/O Select for CTS flow control.
#define DMA_RDYOut_UART1_BIT             BV(5)        // Same as the I/O Select for manual RTS flow ctrl.
// Falling edge ISR on P1.4-7 pins.
#define PICTL_BIT_UART1                  BV(2)
#define IENx_UART1                       IEN2
#define IEN_BIT_UART1                    BV(4)

#if !defined( DMA_PM )
#if defined POWER_SAVING
#define DMA_PM                     0//1  
#else
#define DMA_PM                     0
#endif // POWER_SAVING
#endif // !DMA_PM

// For known defects described above in the moduel description, prefer to drive the Tx by ISR vice
// DMA unless H/W flow control is not used and full-throughput on Tx is absolutely essential.
#if !defined HAL_UART_TX_BY_ISR
#define HAL_UART_TX_BY_ISR         1
#endif

// Minimum delay before allowing sleep and/or clearing DMA ready-out after a DMA ready-in ISR.
// ST-ticks for 6-msecs plus 1 tick added for when the dmaRdyDly is forced from zero to 0xFF.
// If a greater delay than 6-msec is configured, then the logic should be changed to use a uint16.
//efine DMA_PM_DLY_UART1                 198   // 32768 * 0.006 + 1 -> 198.
// This delay should be set as short as possible to work with the max expected latency in the sender
// between its asserting ready-out and its checking of the ready-in response. The RBA Master
// logic in the internal uart-to-uart bridge app checks for ready-in immediately,
// so this is just set to zero.
#define DMA_PM_DLY_UART1                 0

// The timeout tick is at 32-kHz, so multiply msecs by 33.
#define HAL_UART_MSECS_TO_TICKS_UART1    33

#if !defined HAL_UART_DMA_RX_MAX
#define HAL_UART_DMA_RX_MAX        128
#endif
#if !defined HAL_UART_DMA_TX_MAX
#define HAL_UART_DMA_TX_MAX        HAL_UART_DMA_RX_MAX
#endif
#if !defined HAL_UART_DMA_HIGH
#define HAL_UART_DMA_HIGH         (HAL_UART_DMA_RX_MAX - 1)
#endif
#if !defined HAL_UART_DMA_IDLE
#define HAL_UART_DMA_IDLE         (0 * HAL_UART_MSECS_TO_TICKS_UART1)
#endif
#if !defined HAL_UART_DMA_FULL
#define HAL_UART_DMA_FULL         (HAL_UART_DMA_RX_MAX - 16)
#endif

// ST-ticks for 1 byte @ 38.4-kB plus 1 tick added for when the txTick is forced from zero to 0xFF.
#define HAL_UART_TX_TICK_MIN_UART1       11

/* ------------------------------------------------------------------------------------------------
 *                                           TypeDefs
 * ------------------------------------------------------------------------------------------------
 */
/*
#if HAL_UART_DMA_RX_MAX <= 256
typedef uint8 rxIdx_t;
#else
typedef uint16 rxIdx_t;
#endif

#if HAL_UART_DMA_TX_MAX <= 256
typedef uint8 txIdx_t;
#else
typedef uint16 txIdx_t;
#endif
*/

/* ------------------------------------------------------------------------------------------------
 *                                           Macros
 * ------------------------------------------------------------------------------------------------
 */

#define HAL_UART_DMA_NEW_RX_BYTE_UART1(IDX)  ((uint8)DMA_PAD_UART1 == HI_UINT16(dmaCfg.rxBuf[(IDX)]))
#define HAL_UART_DMA_GET_RX_BYTE_UART1(IDX)  (*(volatile uint8 *)(dmaCfg.rxBuf+(IDX)))
#define HAL_UART_DMA_CLR_RX_BYTE_UART1(IDX)  (dmaCfg.rxBuf[(IDX)] = BUILD_UINT16(0, (DMA_PAD_UART1 ^ 0xFF)))

#define HAL_UART_DMA_CLR_RDY_OUT_UART1()     (DMA_RDYOut_UART1 = 1)
#define HAL_UART_DMA_SET_RDY_OUT_UART1()     (DMA_RDYOut_UART1 = 0)

#define HAL_UART_DMA_RDY_IN_UART1()          (DMA_RDYIn_UART1 == 0)
#define HAL_UART_DMA_RDY_OUT_UART1()         (DMA_RDYOut_UART1 == 0)

#if HAL_UART_DMA_RX_MAX == 256
#define HAL_UART_RX_IDX_T_DECR_UART1(IDX)    (IDX)--
#else
#define HAL_UART_RX_IDX_T_DECR_UART1(IDX) st (  \
  if ((IDX)-- == 0) \
  { \
    (IDX) = HAL_UART_DMA_RX_MAX-1; \
  } \
)
#endif

#if HAL_UART_DMA_RX_MAX == 256
#define HAL_UART_RX_IDX_T_INCR_UART1(IDX)    (IDX)++
#else
#define HAL_UART_RX_IDX_T_INCR_UART1(IDX) st (  \
  if (++(IDX) >= HAL_UART_DMA_RX_MAX) \
  { \
    (IDX) = 0; \
  } \
)
#endif

#define HAL_UART_DMA_TX_AVAIL_UART1() \
  ((dmaCfg.txHead > dmaCfg.txTail) ? \
  (dmaCfg.txHead - dmaCfg.txTail - 1) : \
  (HAL_UART_DMA_TX_MAX - dmaCfg.txTail + dmaCfg.txHead - 1))

/* ------------------------------------------------------------------------------------------------
 *                                           Local Variables
 * ------------------------------------------------------------------------------------------------
 */

// The following two variables are only used when POWER_SAVING is defined.
static volatile uint8 dmaRdyIsr;
static uint8 dmaRdyDly;  // Minimum delay before allowing sleep after detecting RdyIn de-asserted.

static uartDMACfg_t dmaCfg;

/* ------------------------------------------------------------------------------------------------
 *                                          Global Functions
 * ------------------------------------------------------------------------------------------------
 */

void HalUART_DMAIsrDMA_UART1(void);

/* ------------------------------------------------------------------------------------------------
 *                                           Local Functions
 * ------------------------------------------------------------------------------------------------
 */

// Invoked by functions in hal_uart.c when this file is included.
static void HalUARTInitDMA_UART1(void);
static void HalUARTOpenDMA_UART1(halUARTCfg_t *config);
static uint16 HalUARTReadDMA_UART1(uint8 *buf, uint16 len);
static uint16 HalUARTWriteDMA_UART1(uint8 *buf, uint16 len);
static void HalUARTPollDMA_UART1(void);
static uint16 HalUARTRxAvailDMA_UART1(void);
static uint8 HalUARTBusyDMA_UART1(void);
#if !HAL_UART_TX_BY_ISR
static void HalUARTPollTxTrigDMA_UART1(void);
static void HalUARTArmTxDMA_UART1(void);
#endif

/******************************************************************************
 * @fn      HalUARTInitDMA
 *
 * @brief   Initialize the UART
 *
 * @param   none
 *
 * @return  none
 *****************************************************************************/
static void HalUARTInitDMA_UART1(void)
{
  halDMADesc_t *ch;
  PERCFG |= HAL_UART_PERCFG_BIT_UART1;     // Set UART1 I/O to Alt. 2 location on P1.
  PxSEL_UART1  |= HAL_UART_Px_SEL_UART1;         // Enable Peripheral control of Rx/Tx on Px.
  UxCSR_UART1 = CSR_MODE_UART1;                  // Mode is UART Mode.
  UxUCR_UART1 = UCR_FLUSH_UART1;                 // Flush it.

  P2DIR &= ~P2DIR_PRIPO_UART1;
  P2DIR |= HAL_UART_PRIPO_UART1;

  if (DMA_PM)
  {
    // Setup GPIO for interrupts by falling edge on DMA_RDY_IN.
    PxIEN_UART1 |= DMA_RDYIn_UART1_BIT;
    PICTL |= PICTL_BIT_UART1;

    HAL_UART_DMA_CLR_RDY_OUT_UART1();
    PxDIR_UART1 |= DMA_RDYOut_UART1_BIT;
  }

#if !HAL_UART_TX_BY_ISR
  // Setup Tx by DMA.
  ch = HAL_DMA_GET_DESC1234( HAL_DMA_CH_TX );

  // Abort any pending DMA operations (in case of a soft reset).
  HAL_DMA_ABORT_CH( HAL_DMA_CH_TX );

  // The start address of the destination.
  HAL_DMA_SET_DEST( ch, DMA_UxDBUF_UART1 );

  // Using the length field to determine how many bytes to transfer.
  HAL_DMA_SET_VLEN( ch, HAL_DMA_VLEN_USE_LEN );

  // One byte is transferred each time.
  HAL_DMA_SET_WORD_SIZE( ch, HAL_DMA_WORDSIZE_BYTE );

  // The bytes are transferred 1-by-1 on Tx Complete trigger.
  HAL_DMA_SET_TRIG_MODE( ch, HAL_DMA_TMODE_SINGLE );
  HAL_DMA_SET_TRIG_SRC( ch, DMATRIG_TX_UART1 );

  // The source address is incremented by 1 byte after each transfer.
  HAL_DMA_SET_SRC_INC( ch, HAL_DMA_SRCINC_1 );

  // The destination address is constant - the Tx Data Buffer.
  HAL_DMA_SET_DST_INC( ch, HAL_DMA_DSTINC_0 );

  // The DMA Tx done is serviced by ISR in order to maintain full thruput.
  HAL_DMA_SET_IRQ( ch, HAL_DMA_IRQMASK_ENABLE );

  // Xfer all 8 bits of a byte xfer.
  HAL_DMA_SET_M8( ch, HAL_DMA_M8_USE_8_BITS );

  // DMA has highest priority for memory access.
  HAL_DMA_SET_PRIORITY( ch, HAL_DMA_PRI_HIGH);
#endif

  // Setup Rx by DMA.
  ch = HAL_DMA_GET_DESC1234( HAL_DMA_CH_RX );

  // Abort any pending DMA operations (in case of a soft reset).
  HAL_DMA_ABORT_CH( HAL_DMA_CH_RX );

  // The start address of the source.
  HAL_DMA_SET_SOURCE( ch, DMA_UxDBUF_UART1 );

  // Using the length field to determine how many bytes to transfer.
  HAL_DMA_SET_VLEN( ch, HAL_DMA_VLEN_USE_LEN );

  /* The trick is to cfg DMA to xfer 2 bytes for every 1 byte of Rx.
   * The byte after the Rx Data Buffer is the Baud Cfg Register,
   * which always has a known value. So init Rx buffer to inverse of that
   * known value. DMA word xfer will flip the bytes, so every valid Rx byte
   * in the Rx buffer will be preceded by a DMA_PAD_UART1 char equal to the
   * Baud Cfg Register value.
   */
  HAL_DMA_SET_WORD_SIZE( ch, HAL_DMA_WORDSIZE_WORD );

  // The bytes are transferred 1-by-1 on Rx Complete trigger.
  HAL_DMA_SET_TRIG_MODE( ch, HAL_DMA_TMODE_SINGLE_REPEATED );
  HAL_DMA_SET_TRIG_SRC( ch, DMATRIG_RX_UART1 );

  // The source address is constant - the Rx Data Buffer.
  HAL_DMA_SET_SRC_INC( ch, HAL_DMA_SRCINC_0 );

  // The destination address is incremented by 1 word after each transfer.
  HAL_DMA_SET_DST_INC( ch, HAL_DMA_DSTINC_1 );
  HAL_DMA_SET_DEST( ch, dmaCfg.rxBuf );
  HAL_DMA_SET_LEN( ch, HAL_UART_DMA_RX_MAX );

  // The DMA is to be polled and shall not issue an IRQ upon completion.
  HAL_DMA_SET_IRQ( ch, HAL_DMA_IRQMASK_DISABLE );

  // Xfer all 8 bits of a byte xfer.
  HAL_DMA_SET_M8( ch, HAL_DMA_M8_USE_8_BITS );

  // DMA has highest priority for memory access.
  HAL_DMA_SET_PRIORITY( ch, HAL_DMA_PRI_HIGH);

  volatile uint8 dummy = *(volatile uint8 *)DMA_UxDBUF_UART1;  // Clear the DMA Rx trigger.
  HAL_DMA_CLEAR_IRQ(HAL_DMA_CH_RX);
  HAL_DMA_ARM_CH(HAL_DMA_CH_RX);
  (void)memset(dmaCfg.rxBuf, (DMA_PAD_UART1 ^ 0xFF), HAL_UART_DMA_RX_MAX * sizeof(uint16));
}

/******************************************************************************
 * @fn      HalUARTOpenDMA
 *
 * @brief   Open a port according tp the configuration specified by parameter.
 *
 * @param   config - contains configuration information
 *
 * @return  none
 *****************************************************************************/
static void HalUARTOpenDMA_UART1(halUARTCfg_t *config)
{
  dmaCfg.uartCB = config->callBackFunc;

  // Only supporting subset of baudrate for code size - other is possible.
  HAL_ASSERT((config->baudRate == HAL_UART_BR_9600) ||
                  (config->baudRate == HAL_UART_BR_19200) ||
                  (config->baudRate == HAL_UART_BR_38400) ||
                  (config->baudRate == HAL_UART_BR_57600) ||
                  (config->baudRate == HAL_UART_BR_115200));

  if (config->baudRate == HAL_UART_BR_57600 ||
      config->baudRate == HAL_UART_BR_115200)
  {
    UxBAUD_UART1 = 216;
  }
  else
  {
    UxBAUD_UART1 = 59;
  }

  switch (config->baudRate)
  {
    case HAL_UART_BR_9600:
      UxGCR_UART1 = 8;
      break;
    case HAL_UART_BR_19200:
      UxGCR_UART1 = 9;
      break;
    case HAL_UART_BR_38400:
    case HAL_UART_BR_57600:
      UxGCR_UART1 = 10;
      break;
    default:
      // HAL_UART_BR_115200
      UxGCR_UART1 = 11;
      break;
  }

  if (DMA_PM || config->flowControl)
  {
    UxUCR_UART1 = UCR_FLOW_UART1 | UCR_STOP_UART1;      // 8 bits/char; no parity; 1 stop bit; stop bit hi.
    PxSEL_UART1 |= HAL_UART_Px_CTS_UART1;         // Enable Peripheral control of CTS flow control on Px.
  }
  else
  {
    UxUCR_UART1 = UCR_STOP_UART1;                 // 8 bits/char; no parity; 1 stop bit; stop bit hi.
  }

  UxCSR_UART1 = (CSR_MODE_UART1 | CSR_RE_UART1);

  if (DMA_PM)
  {
    PxIFG_UART1 = 0;
    PxIF = 0;
    IENx_UART1 |= IEN_BIT_UART1;
  }
  else if (UxUCR_UART1 & UCR_FLOW_UART1)
  {
    // DMA Rx is always on (self-resetting). So flow must be controlled by the S/W polling the
    // circular Rx queue depth. Start by allowing flow.
    HAL_UART_DMA_SET_RDY_OUT_UART1();
    PxDIR_UART1 |= HAL_UART_Px_RTS_UART1;
  }

#if HAL_UART_TX_BY_ISR
  UTXxIF_UART1 = 1;  // Prime the ISR pump.
#endif
}

/*****************************************************************************
 * @fn      HalUARTReadDMA
 *
 * @brief   Read a buffer from the UART
 *
 * @param   buf  - valid data buffer at least 'len' bytes in size
 *          len  - max length number of bytes to copy to 'buf'
 *
 * @return  length of buffer that was read
 *****************************************************************************/
static uint16 HalUARTReadDMA_UART1(uint8 *buf, uint16 len)
{
  uint16 cnt;

  for (cnt = 0; cnt < len; cnt++)
  {
    if (!HAL_UART_DMA_NEW_RX_BYTE_UART1(dmaCfg.rxHead))
    {
      break;
    }
    *buf++ = HAL_UART_DMA_GET_RX_BYTE_UART1(dmaCfg.rxHead);
    HAL_UART_DMA_CLR_RX_BYTE_UART1(dmaCfg.rxHead);
    HAL_UART_RX_IDX_T_INCR_UART1(dmaCfg.rxHead);
  }

  /* Update pointers after reading the bytes */
  dmaCfg.rxTail = dmaCfg.rxHead;

  if (!DMA_PM && (UxUCR_UART1 & UCR_FLOW_UART1))
  {
    HAL_UART_DMA_SET_RDY_OUT_UART1();  // Re-enable the flow asap (i.e. not wait until next uart poll).    
  }

  return cnt;
}

/******************************************************************************
 * @fn      HalUARTWriteDMA
 *
 * @brief   Write a buffer to the UART, enforcing an all or none policy if the requested length
 *          exceeds the space available.
 *
 * @param   buf - pointer to the buffer that will be written, not freed
 *          len - length of
 *
 * @return  length of the buffer that was sent
 *****************************************************************************/
static uint16 HalUARTWriteDMA_UART1(uint8 *buf, uint16 len)
{
#if HAL_UART_TX_BY_ISR
  // Enforce all or none.
  if (HAL_UART_DMA_TX_AVAIL_UART1() < len)
  {
    return 0;
  }

  for (uint16 cnt = 0; cnt < len; cnt++)
  {
    dmaCfg.txBuf[dmaCfg.txTail] = *buf++;
    dmaCfg.txMT = 0;

    if (dmaCfg.txTail >= HAL_UART_DMA_TX_MAX-1)
    {
      dmaCfg.txTail = 0;
    }
    else
    {
      dmaCfg.txTail++;
    }

    // Keep re-enabling ISR as it might be keeping up with this loop due to other ints.
    IEN2 |= UTXxIE_UART1;
  }
#else
  txIdx_t txIdx;
  uint8 txSel;
  halIntState_t his;

  HAL_ENTER_CRITICAL_SECTION(his);
  txSel = dmaCfg.txSel;
  txIdx = dmaCfg.txIdx[txSel];
  HAL_EXIT_CRITICAL_SECTION(his);

  // Enforce all or none.
  if ((len + txIdx) > HAL_UART_DMA_TX_MAX)
  {
    return 0;
  }

  (void)memcpy(&(dmaCfg.txBuf[txSel][txIdx]), buf, len);

  HAL_ENTER_CRITICAL_SECTION(his);
  /* If an ongoing DMA Tx finished while this buffer was being *appended*, then another DMA Tx
   * will have already been started on this buffer, but it did not include the bytes just appended.
   * Therefore these bytes have to be re-copied to the start of the new working buffer.
   */
  if (txSel != dmaCfg.txSel)
  {
    HAL_EXIT_CRITICAL_SECTION(his);
    txSel ^= 1;

    (void)memcpy(&(dmaCfg.txBuf[txSel][0]), buf, len);
    HAL_ENTER_CRITICAL_SECTION(his);
    dmaCfg.txIdx[txSel] = len;
  }
  else
  {
    dmaCfg.txIdx[txSel] = txIdx + len;
  }

  // If there is no ongoing DMA Tx, then the channel must be armed here.
  if (dmaCfg.txIdx[(txSel ^ 1)] == 0)
  {
    HAL_EXIT_CRITICAL_SECTION(his);
    HalUARTArmTxDMA_UART1();
  }
  else
  {
    dmaCfg.txMT = FALSE;
    HAL_EXIT_CRITICAL_SECTION(his);
  }
#endif

  return len;
}

/******************************************************************************
 * @fn      HalUARTPollDMA
 *
 * @brief   Poll a USART module implemented by DMA, including the hybrid solution in which the Rx
 *          is driven by DMA but the Tx is driven by ISR.
 *
 * @param   none
 *
 * @return  none
 *****************************************************************************/
static void HalUARTPollDMA_UART1(void)
{
  uint8 evt = 0;
  uint16 cnt;

#if DMA_PM
  PxIEN_UART1 &= ~DMA_RDYIn_UART1_BIT;  // Clear to not race with DMA_RDY_IN ISR.
  {
    if (dmaRdyIsr || HAL_UART_DMA_RDY_IN_UART1() || HalUARTBusyDMA_UART1())
    {
      // Master may have timed-out the SRDY asserted state & may need a new edge.
#if HAL_UART_TX_BY_ISR
      if (!HAL_UART_DMA_RDY_IN_UART1() && (dmaCfg.txHead != dmaCfg.txTail))
#else
      if (!HAL_UART_DMA_RDY_IN_UART1() && ((dmaCfg.txIdx[0] != 0) || (dmaCfg.txIdx[1] != 0)))
#endif
      {
        HAL_UART_DMA_CLR_RDY_OUT_UART1();
      }
      dmaRdyIsr = 0;

      if (dmaRdyDly == 0)
      {
        (void)osal_set_event(Hal_TaskID, HAL_PWRMGR_HOLD_EVENT);
      }

      if ((dmaRdyDly = ST0) == 0)  // Reserve zero to signify that the delay expired.
      {
        dmaRdyDly = 0xFF;
      }
      HAL_UART_DMA_SET_RDY_OUT_UART1();
    }
    else if ((dmaRdyDly != 0) && (!DMA_PM_DLY_UART1 || ((uint8)(ST0 - dmaRdyDly) > DMA_PM_DLY_UART1)))
    {
      dmaRdyDly = 0;
      (void)osal_set_event(Hal_TaskID, HAL_PWRMGR_CONSERVE_EVENT);
    }
  }
  PxIEN_UART1 |= DMA_RDYIn_UART1_BIT;
#endif

#if !HAL_UART_TX_BY_ISR
  HalUARTPollTxTrigDMA_UART1();
#endif


  cnt = HalUARTRxAvailDMA_UART1();  // Wait to call until after the above DMA Rx bug work-around.

#if HAL_UART_DMA_IDLE
  if (dmaCfg.rxTick)
  {
    // Use the LSB of the sleep timer (ST0 must be read first anyway) to measure the Rx timeout.
    if ((ST0 - dmaCfg.rxTick) > HAL_UART_DMA_IDLE)
    {
      dmaCfg.rxTick = 0;
      evt = HAL_UART_RX_TIMEOUT;
    }
  }
  else if (cnt != 0)
  {
    if ((dmaCfg.rxTick = ST0) == 0)  // Zero signifies that the Rx timeout is not running.
    {
      dmaCfg.rxTick = 0xFF;
    }
  }
#else
  if (cnt != 0)
  {
    evt = HAL_UART_RX_TIMEOUT;
  }
#endif

  if (cnt >= HAL_UART_DMA_FULL)
  {
    evt |= HAL_UART_RX_FULL;
  }
  else if (cnt >= HAL_UART_DMA_HIGH)
  {
    evt |= HAL_UART_RX_ABOUT_FULL;

    if (!DMA_PM && (UxUCR_UART1 & UCR_FLOW_UART1))
    {
      HAL_UART_DMA_CLR_RDY_OUT_UART1();  // Disable Rx flow.
    }
  }

  if (dmaCfg.txMT)
  {
    dmaCfg.txMT = FALSE;
    evt |= HAL_UART_TX_EMPTY;
  }

  if ((evt != 0) && (dmaCfg.uartCB != NULL))
  {
    dmaCfg.uartCB(HAL_UART_DMA-1, evt);
  }

  if (DMA_PM && (dmaRdyDly == 0) && !HalUARTBusyDMA_UART1())
  {
    HAL_UART_DMA_CLR_RDY_OUT_UART1();
  }
}

/**************************************************************************************************
 * @fn      HalUARTRxAvailDMA()
 *
 * @brief   Calculate Rx Buffer length - the number of bytes in the buffer.
 *
 * @param   none
 *
 * @return  length of current Rx Buffer
 **************************************************************************************************/
static uint16 HalUARTRxAvailDMA_UART1(void)
{
  uint16 cnt = 0;
  // First, synchronize the Rx tail marker with where the DMA Rx engine is working.
  rxIdx_t tail = dmaCfg.rxTail;

#ifndef POWER_SAVING
  if (!DMA_PM && (UxUCR_UART1 & UCR_FLOW_UART1))
  {
    HAL_UART_DMA_CLR_RDY_OUT_UART1();  // Stop the inflow for counting the bytes
  }
#endif

  do
  {
    if (!HAL_UART_DMA_NEW_RX_BYTE_UART1(tail))
    {
      break;
    }
    else
    {
      cnt++;
    }
    HAL_UART_RX_IDX_T_INCR_UART1(tail);
  } while (cnt  < HAL_UART_DMA_RX_MAX);

#ifndef POWER_SAVING
  if ( !DMA_PM && (UxUCR_UART1 & UCR_FLOW_UART1) )
  {
    HAL_UART_DMA_SET_RDY_OUT_UART1();  // Re-enable the flow asap
  }
#endif
  return cnt;
}

/******************************************************************************
 * @fn      HalUARTBusyDMA
 *
 * @brief   Query the UART hardware & buffers before entering PM mode 1, 2 or 3.
 *
 * @param   None
 *
 * @return  TRUE if the UART H/W is busy or buffers are not empty; FALSE otherwise.
 *****************************************************************************/
static uint8 HalUARTBusyDMA_UART1( void )
{
#if HAL_UART_TX_BY_ISR
  return !((!(UxCSR_UART1 & (CSR_ACTIVE_UART1 | CSR_RX_BYTE_UART1))) && (HalUARTRxAvailDMA_UART1() == 0) &&
           (dmaCfg.txHead == dmaCfg.txTail));
#else
  return !((!(UxCSR_UART1 & (CSR_ACTIVE_UART1 | CSR_RX_BYTE_UART1))) && (HalUARTRxAvailDMA_UART1() == 0) &&
           (dmaCfg.txIdx[0] == 0) && (dmaCfg.txIdx[1] == 0));
#endif
}

#if !HAL_UART_TX_BY_ISR
/******************************************************************************
 * @fn      HalUARTPollTxTrigDMA
 *
 * @brief   Ascertain whether a manual trigger is required for the DMA Tx channel.
 *
 * @param   None
 *
 * @return  None
 *****************************************************************************/
static void HalUARTPollTxTrigDMA_UART1(void)
{
  if ((UxCSR_UART1 & CSR_TX_BYTE_UART1) == 0)  // If no TXBUF to shift register transfer, then TXBUF may be MT.
  {
    if ((dmaCfg.txTick == 0) || ((uint8)(ST0 - dmaCfg.txTick) > HAL_UART_TX_TICK_MIN_UART1))
    {
      dmaCfg.txTick = 0;

      if (dmaCfg.txTrig && HAL_DMA_CH_ARMED(HAL_DMA_CH_TX))
      {
        HAL_DMA_MAN_TRIGGER(HAL_DMA_CH_TX);
      }
      dmaCfg.txTrig = 0;
    }
  }
  else
  {
    UxCSR_UART1 = (CSR_MODE_UART1 | CSR_RE_UART1);  // Clear the CSR_TX_BYTE_UART1 flag.
    dmaCfg.txTick = ST0;

    if (dmaCfg.txTick == 0)  // Reserve zero to signify that the minimum delay has been met.
    {
      dmaCfg.txTick = 0xFF;
    }
  }
}

/******************************************************************************
 * @fn      HalUARTArmTxDMA
 *
 * @brief   Arm the Tx DMA channel.
 *
 * @param   None
 *
 * @return  None
 *****************************************************************************/
static void HalUARTArmTxDMA_UART1(void)
{
  halDMADesc_t *ch = HAL_DMA_GET_DESC1234(HAL_DMA_CH_TX);
  HAL_DMA_SET_SOURCE(ch, dmaCfg.txBuf[dmaCfg.txSel]);
  HAL_DMA_SET_LEN(ch, dmaCfg.txIdx[dmaCfg.txSel]);

  dmaCfg.txSel ^= 1;
  dmaCfg.txTrig = 1;
  HAL_DMA_ARM_CH(HAL_DMA_CH_TX);
 
  /* Time to arm each DMA channel is 9 cycles as per the user's guide */
  asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
  asm("nop"); asm("nop"); asm("nop"); asm("nop"); 

  HalUARTPollTxTrigDMA_UART1();

  if (DMA_PM)
  {
    HAL_UART_DMA_SET_RDY_OUT_UART1();
  }
}
#endif

/******************************************************************************
 * @fn      HalUART_DMAIsrDMA_UART1
 *
 * @brief   Handle the Tx done DMA ISR.
 *
 * @param   none
 *
 * @return  none
 *****************************************************************************/
void HalUART_DMAIsrDMA_UART1(void)
{
#if !HAL_UART_TX_BY_ISR
  if (dmaCfg.txIdx[dmaCfg.txSel])
  {
    // If there is more Tx data ready to go, re-arm the DMA immediately on it.
    HalUARTArmTxDMA_UART1();

    // Indicate that the Tx buffer just finished is now free (re-arming did a ^= toggle of txSel).
    dmaCfg.txIdx[dmaCfg.txSel] = 0;
  }
  else
  {
    dmaCfg.txIdx[(dmaCfg.txSel ^ 1)] = 0;  // Indicate that the Tx buffer just finished is now free.

    // Clear the CSR_TX_BYTE_UART1 flag & start the txTick to allow the possibility of an immediate
    // manual trigger from the next Write(), if it occurs more than one character time later.
    HalUARTPollTxTrigDMA_UART1();
  }

  dmaCfg.txMT = TRUE;  // Notify CB that at least one Tx buffer is now free to use.
#endif
}

#if DMA_PM
/**************************************************************************************************
 * @fn      PortX Interrupt Handler
 *
 * @brief   This function is the PortX interrupt service routine.
 *
 * @param   None.
 *
 * @return  None.
 *************************************************************************************************/
HAL_ISR_FUNCTION(port1Isr, P1INT_VECTOR)
{
  HAL_ENTER_ISR();

  PxIFG_UART1 = 0;
  PxIF = 0;

  dmaRdyIsr = 1;

#ifdef POWER_SAVING
  CLEAR_SLEEP_MODE();
 (void)osal_pwrmgr_task_state(Hal_TaskID, PWRMGR_HOLD);

#if HAL_UART_TX_BY_ISR 
  if ( dmaCfg.txHead == dmaCfg.txTail )
  {
    HAL_UART_DMA_CLR_RDY_OUT_UART1();
  }
#endif
#endif
  HAL_EXIT_ISR();
}
#endif

#if HAL_UART_TX_BY_ISR
/***************************************************************************************************
 * @fn      halUartTxIsr
 *
 * @brief   UART Transmit Interrupt
 *
 * @param   None
 *
 * @return  None
 ***************************************************************************************************/
HAL_ISR_FUNCTION( halUart1TxIsr, UTX1_VECTOR )
{
  HAL_ENTER_ISR();

  if (dmaCfg.txHead == dmaCfg.txTail)
  {
    IEN2 &= ~UTXxIE_UART1;
    dmaCfg.txMT = 1;
  }
  else
  {
    UTXxIF_UART1 = 0;
    UxDBUF_UART1 = dmaCfg.txBuf[dmaCfg.txHead++];

    if ((HAL_UART_DMA_TX_MAX != 256) && (dmaCfg.txHead >= HAL_UART_DMA_TX_MAX))
    {
      dmaCfg.txHead = 0;
    }
  }

  HAL_EXIT_ISR();
}
#endif

/**************************************************************************************************
*/
