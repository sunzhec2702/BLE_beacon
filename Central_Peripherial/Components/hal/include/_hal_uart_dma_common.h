#ifndef __HAL_UART_DMA_COMMON_H_
#define __HAL_UART_DMA_COMMON_H_

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

// UxCSR - USART Control and Status Register.
#define CSR_MODE                   0x80
#define CSR_RE                     0x40
#define CSR_SLAVE                  0x20
#define CSR_FE                     0x10
#define CSR_ERR                    0x08
#define CSR_RX_BYTE                0x04
#define CSR_TX_BYTE                0x02
#define CSR_ACTIVE                 0x01

// UxUCR - USART UART Control Register.
#define UCR_FLUSH                  0x80
#define UCR_FLOW                   0x40
#define UCR_D9                     0x20
#define UCR_BIT9                   0x10
#define UCR_PARITY                 0x08
#define UCR_SPB                    0x04
#define UCR_STOP                   0x02
#define UCR_START                  0x01

#define UTX0IE                     0x04
#define UTX1IE                     0x08

#define P2DIR_PRIPO                0xC0

#define HAL_DMA_U0DBUF             0x70C1
#define HAL_DMA_U1DBUF             0x70F9

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
//efine DMA_PM_DLY                 198   // 32768 * 0.006 + 1 -> 198.
// This delay should be set as short as possible to work with the max expected latency in the sender
// between its asserting ready-out and its checking of the ready-in response. The RBA Master
// logic in the internal uart-to-uart bridge app checks for ready-in immediately,
// so this is just set to zero.
#define DMA_PM_DLY                 0

// The timeout tick is at 32-kHz, so multiply msecs by 33.
#define HAL_UART_MSECS_TO_TICKS    33

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
#define HAL_UART_DMA_IDLE         (0 * HAL_UART_MSECS_TO_TICKS)
#endif
#if !defined HAL_UART_DMA_FULL
#define HAL_UART_DMA_FULL         (HAL_UART_DMA_RX_MAX - 16)
#endif

// ST-ticks for 1 byte @ 38.4-kB plus 1 tick added for when the txTick is forced from zero to 0xFF.
#define HAL_UART_TX_TICK_MIN       11

/* ------------------------------------------------------------------------------------------------
 *                                           TypeDefs
 * ------------------------------------------------------------------------------------------------
 */

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

typedef struct
{
  uint16 rxBuf[HAL_UART_DMA_RX_MAX];
  rxIdx_t rxHead;
  rxIdx_t rxTail;
#if HAL_UART_DMA_IDLE
  uint8 rxTick;
#endif

#if HAL_UART_TX_BY_ISR
  uint8 txBuf[HAL_UART_DMA_TX_MAX];
  volatile txIdx_t txHead;
  txIdx_t txTail;
  uint8 txMT;
#else
  uint8 txBuf[2][HAL_UART_DMA_TX_MAX];
  txIdx_t txIdx[2];
  uint8 txMT;    // Indication that at least one of two Tx buffers are free.
  uint8 txTick;  // ST ticks of delay to allow at least one byte-time at a given baud rate.
  uint8 txTrig;  // Flag indicating that Tx should be manually triggered after txTick expires.

  // Although all of the txVars above are modified by the Tx-done ISR, only this one should need
  // the special volatile consideration by the optimizer (critical sections protect the rest).
  volatile uint8 txSel;
#endif

  halUARTCBack_t uartCB;
} uartDMACfg_t;


#endif