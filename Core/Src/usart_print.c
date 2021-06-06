/**
  ******************************************************************************
  * @file    usart_print.c
  * @brief   
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart_print.h"

#include "stdio.h"
#include "stdarg.h"

# define UART_TX_BUF_SIZE         128U

static const char *level_string[] = {
  "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
};


#ifdef LOG_USE_COLOR
static const char *level_colors[] = {
  "\x1b[36m", "\x1b[32m", "\x1b[33m", "\x1b[31m", "\x1b[35m"
};
#endif


uint8_t txbuffer[UART_TX_BUF_SIZE];
static int log_level = LOG_DEBUG;


/* USER CODE BEGIN 0 */

/* USER CODE END 0 */


/* USART Print function */

UsartPrintErrCodeType UsartPrint(UART_HandleTypeDef *ptr2usartHandle, const char * format, ... ){
  
  HAL_StatusTypeDef respErrValue;
  
  uint32_t len;
	va_list argptr;

  va_start(argptr, format);
  len = vsprintf((char*)txbuffer, format, argptr);
  va_end(argptr);
  
  respErrValue = HAL_UART_Transmit(ptr2usartHandle, txbuffer, len, 100);
    
  if(respErrValue == HAL_ERROR){
    return UsartPrintERROR;
  }else if(respErrValue == HAL_TIMEOUT){
    return UsartPrintTimeoutERROR;
  }else{
    return UsartPrintnoERROR;
  }
  
}


UsartPrintErrCodeType UsartPrintLogMsg(UART_HandleTypeDef *ptr2usartHandle, int level, const char *file, int line, const char * format, ...){
  
  HAL_StatusTypeDef respErrValue;
  
  uint32_t len;
	va_list argptr;
  
  
  
  if(level >= log_level){
#ifdef LOG_USE_COLOR
    len = sprintf((char*)txbuffer, "%s%-5s\x1b[0m \x1b[90m%s:%d:\x1b[0m ", level_colors[level], level_string[level], file, line);
#else
    len = sprintf((char*)txbuffer, "%-5s %s:%d: ", level_string[level], file, line);  
#endif   
  }
  
  len = sprintf((char*)txbuffer, "%s%s", txbuffer, format);
  
  va_start(argptr, format);
  len = vsprintf((char*)txbuffer, (const char*)txbuffer, argptr);
  va_end(argptr);
  
  respErrValue = HAL_UART_Transmit(ptr2usartHandle, txbuffer, len, 100);
  
  if(respErrValue == HAL_ERROR){
    return UsartPrintERROR;
  }else if(respErrValue == HAL_TIMEOUT){
    return UsartPrintTimeoutERROR;
  }else{
    return UsartPrintnoERROR;
  }
  
}
  



/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
