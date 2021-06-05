#include "printf.h"

#include "stdio.h"
#include "stdarg.h"
#include "string.h"
#include "usart.h"

char txbuffer[UART_TX_BUF_SIZE];

uint8_t sprint(const char * format, ...){

	uint32_t len;
	va_list argptr;

    va_start(argptr, format);
    len = vsprintf((char*)txbuffer, format, argptr);
    va_end(argptr);

    return HAL_UART_Transmit(&UART_INSTANCE, txbuffer, len, UART_TIMEOUT);
}

uint8_t sprintln(const char * format, ...){

    uint32_t len;
	va_list argptr;

    va_start(argptr, format);
    len = vsprintf((char*)txbuffer, format, argptr);
    va_end(argptr);

    strcat((char*)txbuffer+len,"\r\n");
    len += 2;

    return HAL_UART_Transmit(&UART_INSTANCE, txbuffer, len, UART_TIMEOUT);
}