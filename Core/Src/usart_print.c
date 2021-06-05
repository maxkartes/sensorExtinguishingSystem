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


uint8_t txbuffer[UART_TX_BUF_SIZE];


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



/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
