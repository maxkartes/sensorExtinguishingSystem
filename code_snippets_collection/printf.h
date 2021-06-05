#ifndef PRINTF_H_
#define PRINTF_H_

#define UART_TX_BUF_SIZE 256
#define UART_RX_BUF_SIZE 256
#define UART_TIMEOUT 100
#define UART_INSTANCE huart1

uint8_t sprint(const char * format, ...);
uint8_t sprintln(const char * format, ...);

#endif /* CONSOLE_H_ */