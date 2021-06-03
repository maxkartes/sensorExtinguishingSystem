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
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common

#define POWER_OF_TWO_SHIFT_INDX         7
#define NMB_OF_ADC_SAMPLES              (1 << POWER_OF_TWO_SHIFT_INDX)


struct __MiCS5524Descriptor
{
  ADC_HandleTypeDef *adcHandle;
  volatile uint32_t rawADCValue;               /*!< Raw 32 bit ADC Value of DR */
  volatile uint32_t offset;
};

static MiCS5524DescriptorType MiCS5524descr;


MiCS5524ErrCodeType MiCS5524init(ADC_HandleTypeDef* adcHandle, MiCS5524HandleType * ptr2MiCS5524Handle){
  
  MiCS5524HandleType const MiCS5524Handle = &MiCS5524descr;
  
  MiCS5524Handle->adcHandle = adcHandle;
  
  *ptr2MiCS5524Handle = MiCS5524Handle;
  
  return MiCS5524noERROR;
    
}




uint32_t MICS5524_readValue(MiCS5524HandleType MiCS5524Handle){
  
  ADC_HandleTypeDef * const ptr2adcHandle = MiCS5524Handle->adcHandle;
  
  HAL_StatusTypeDef respErrValue;
  
  
  respErrValue =  HAL_ADC_Start(ptr2adcHandle);
  
  if(respErrValue == HAL_ERROR){
    return 0;
  }else if(respErrValue == HAL_TIMEOUT){
    return 0;
  }
    
  respErrValue = HAL_ADC_PollForConversion(ptr2adcHandle,10);
  
  if(respErrValue == HAL_ERROR){
    return 0;
  }else if(respErrValue == HAL_TIMEOUT){
    return 0;
  }
    
   
   return HAL_ADC_GetValue(ptr2adcHandle);
     
}


MiCS5524ErrCodeType MICS5524_getValue(MiCS5524HandleType MiCS5524Handle){
  
  ADC_HandleTypeDef * const ptr2adcHandle = MiCS5524Handle->adcHandle;
  
  HAL_StatusTypeDef respErrValue;
  
  
  respErrValue =  HAL_ADC_Start(ptr2adcHandle);
  
  if(respErrValue == HAL_ERROR){
    return MiCS5524HALError;
  }else if(respErrValue == HAL_TIMEOUT){
    return MiCS5524timeoutERROR;
  }
    
  respErrValue = HAL_ADC_PollForConversion(ptr2adcHandle,10);
  
  if(respErrValue == HAL_ERROR){
    return MiCS5524HALError;
  }else if(respErrValue == HAL_TIMEOUT){
    return MiCS5524timeoutERROR;
  }
    
  MiCS5524Handle->rawADCValue = HAL_ADC_GetValue(ptr2adcHandle);
  return MiCS5524noERROR;
     
}

MiCS5524ErrCodeType MICS5524_calcOffsetComp(MiCS5524HandleType MiCS5524Handle){
  
  ADC_HandleTypeDef * const ptr2adcHandle = MiCS5524Handle->adcHandle;  
  HAL_StatusTypeDef respErrValue;
  
  uint32_t ADCValueBuffer[NMB_OF_ADC_SAMPLES];
  uint32_t sumADCValues = 0;
  
  for(uint32_t i = 0; i < NMB_OF_ADC_SAMPLES; i++){
    
    respErrValue =  HAL_ADC_Start(ptr2adcHandle);
  
    if(respErrValue == HAL_ERROR){
      return MiCS5524HALError;
    }else if(respErrValue == HAL_TIMEOUT){
      return MiCS5524timeoutERROR;
    }      
    
    respErrValue = HAL_ADC_PollForConversion(ptr2adcHandle,100);
  
    if(respErrValue == HAL_ERROR){
      return MiCS5524HALError;
    }else if(respErrValue == HAL_TIMEOUT){
      return MiCS5524timeoutERROR;
    }
    
    ADCValueBuffer[i] = HAL_ADC_GetValue(ptr2adcHandle);
    HAL_Delay(100);
    
  }
  
  for(uint32_t i = 0; i < NMB_OF_ADC_SAMPLES; i++){
    sumADCValues = sumADCValues + ADCValueBuffer[i];   
  }
  
  MiCS5524Handle->offset =  sumADCValues >> POWER_OF_TWO_SHIFT_INDX;   // ((sumADCValues * sizeof(ADCValueBuffer[0])) /sizeof(ADCValueBuffer));
  
    
  return MiCS5524noERROR;
   
    
}




/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

