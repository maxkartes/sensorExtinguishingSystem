/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
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
#ifndef __DRVSCD30_H__
#define __DRVSCD30_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

uint16_t SCD30_readRegister(I2C_HandleTypeDef* i2cHandle, uint16_t registerAddress);



/* USER CODE BEGIN Private defines */
#define SCD30_BASE_ADDRESS  0xC2

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __DRVSCD30_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
