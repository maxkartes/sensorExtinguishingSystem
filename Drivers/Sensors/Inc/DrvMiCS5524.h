/**
  ******************************************************************************
  * @file    DrvMiCS5524.h
  * @brief   This file contains all the function prototypes for
  *          the DrvMiCS5524.c file
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
#ifndef __DRVMICS5524_H__
#define __DRVMICS5524_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"




uint32_t MICS5524_readValue(ADC_HandleTypeDef* adcHandle);





/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __DRVMICS5524_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
