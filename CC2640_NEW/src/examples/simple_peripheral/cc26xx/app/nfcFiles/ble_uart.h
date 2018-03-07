#ifndef __BLE_UART_H
#define __BLE_UART_H

void bleUartRxCallback(void);

//serial_port uart_open(const char *pcPortName);
//void    uart_close();
void    uart_flush_input(bool wait);

//void    uart_set_speed(serial_port sp, const uint32_t uiPortSpeed);
//uint32_t uart_get_speed(const serial_port sp);

int uart_receive(uint8_t *pbtRx, const uint16_t szRx, void *abort_p, int timeout);
int uart_send(const uint8_t *pbtTx, const uint16_t szTx, int timeout);
void ble_uart_init(void);

//char  **uart_list_ports(void);

#endif
