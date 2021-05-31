/**
  ******************************************************************************
  * @file    DrvMiCS5524.c
  * @brief   This file provides code for the configuration
  *          of the MiC5524 instances.
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
#include "DrvMiCS5524.h"

#include "stm32f4xx_hal_def.h"

uint32_t MICS5524_readValue(ADC_HandleTypeDef* adcHandle){
  
  HAL_StatusTypeDef respErrValue;
  
  
  respErrValue =  HAL_ADC_Start(adcHandle);
  
  if(respErrValue == HAL_ERROR){
    return -1;
  }else if(respErrValue == HAL_TIMEOUT){
    return -1;
  }
    
  respErrValue = HAL_ADC_PollForConversion(adcHandle,10);
  
  if(respErrValue == HAL_ERROR){
    return -1;
  }else if(respErrValue == HAL_TIMEOUT){
    return -1;
  }
    
    
   return HAL_ADC_GetValue(adcHandle);
     
}


/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

