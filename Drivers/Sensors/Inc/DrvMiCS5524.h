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

typedef enum {
  MiCS5524noERROR,                 ///< all ok
  MiCS5524InvalidParameter,        ///< at least one parameter was invalid when calling the function
  MiCS5524isReady,                 ///< ready ststus register
  MiCS5524timeoutERROR,            ///< 
  MiCS5524HALError,
} MiCS5524ErrCodeType;


struct __MiCS5524Descriptor;     // incomplte type !

/// Datentyp zur Beschreibung des vollstaendigen Kontextes einer SCD30 Instanz
typedef struct __MiCS5524Descriptor MiCS5524DescriptorType;

typedef MiCS5524DescriptorType *MiCS5524HandleType;


MiCS5524ErrCodeType MiCS5524init(ADC_HandleTypeDef* adcHandle, MiCS5524HandleType * ptr2MiCS5524Handle);

uint32_t MICS5524_readValue(MiCS5524HandleType MiCS5524Handle);

MiCS5524ErrCodeType MICS5524_getValue(MiCS5524HandleType MiCS5524Handle);

MiCS5524ErrCodeType MICS5524_calcOffsetComp(MiCS5524HandleType MiCS5524Handle, uint32_t NmbOfADCSamples);


/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __DRVMICS5524_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
