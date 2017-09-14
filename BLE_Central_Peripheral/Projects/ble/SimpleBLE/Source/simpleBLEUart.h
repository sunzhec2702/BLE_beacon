#ifndef __BLE_UART_H
#define __BLE_UART_H

void ble_uart_init(void);
void NpiSerialCallback(uint8 port, uint8 events);
void ble_command_parse(uint8 *buffer, uint8 numBytes);
void ble_process_command(uint8 *buffer);

#endif