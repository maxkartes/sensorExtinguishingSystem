/**
  ******************************************************************************
  * @file    usart_print.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_PRINT_H__
#define __USART_PRINT_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#include "stdio.h"
#include "stdarg.h"
#include "stdbool.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */


/* USER CODE BEGIN Private defines */

typedef enum {  
  UsartPrintnoERROR,                 ///< all ok
  UsartPrintERROR,                   ///< HAL Error 
  UsartPrintisBusy,                  ///< ready ststus register
  UsartPrintTimeoutERROR,            ///< timeout error
  UsartPrintInvalidParameter,        ///< at least one parameter was invalid when calling the function
} UsartPrintErrCodeType;


enum { LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR, LOG_FATAL };

#define log_debug(...) UsartPrintLogMsg(&huart2, LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define log_info(...)  UsartPrintLogMsg(&huart2, LOG_INFO,  __FILE__, __LINE__, __VA_ARGS__)
#define log_warn(...)  UsartPrintLogMsg(&huart2, LOG_WARN,  __FILE__, __LINE__, __VA_ARGS__)
#define log_error(...) UsartPrintLogMsg(&huart2, LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define log_fatal(...) UsartPrintLogMsg(&huart2, LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)

/* USER CODE END Private defines */

UsartPrintErrCodeType UsartPrint(UART_HandleTypeDef *ptr2usartHandle, const char * format, ... );

UsartPrintErrCodeType UsartPrintLogMsg(UART_HandleTypeDef *ptr2usartHandle, int level, const char *file, int line, const char * format, ...);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */





#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

