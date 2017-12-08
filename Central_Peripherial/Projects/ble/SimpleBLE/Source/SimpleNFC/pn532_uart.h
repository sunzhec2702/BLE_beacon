/**
 * @file pn532_uart.h
 * @brief Driver for PN532 connected in UART (HSU)
 */

#ifndef __NFC_DRIVER_PN532_UART_H__
#define __NFC_DRIVER_PN532_UART_H__

#include "nfc-types.h"

struct pn532_uart_data {
  //serial_port port;
  int iAbortFds[2];
};

#define DRIVER_DATA(pnd) ((struct pn532_uart_data*)(pnd->driver_data))

extern const struct nfc_driver pn532_uart_driver;
extern struct pn532_uart_data;
extern const struct pn53x_io pn532_uart_io;

#endif // ! __NFC_DRIVER_PN532_UART_H__
