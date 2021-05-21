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


typedef enum {
  SCDnoERROR,                 ///< all ok
  SCDInvalidParameter,        ///< at least one parameter was invalid when calling the function
  SCDisReady,                 ///< ready ststus register
  SCDnoAckERROR,              ///< no I2C ACK error
  SCDtimeoutERROR,            ///< I2C timeout error
  SCDcrcERROR,                ///< CRC error, any
  SCDcrcERRORv1,              ///< CRC error on value 1
  SCDcrcERRORv2,              ///< CRC error on value 2
  SCDcrcERRORv3,              ///< CRC error on value 3
  SCDcrcERRORv4,              ///< CRC error on value 4
  SCDcrcERRORv5,              ///< CRC error on value 5
  SCDcrcERRORv6,              ///< CRC error on value 6
} SCD30ErrCodeType;


struct __SCD30Descriptor;     // incomplte type !

/// Datentyp zur Beschreibung des vollstaendigen Kontextes einer SCD30 Instanz
typedef struct __SCD30Descriptor SCD30DescriptorType;

typedef SCD30DescriptorType *SCD30HandleType;

SCD30ErrCodeType SCD30init(SCD30HandleType * ptr2Handle);

SCD30ErrCodeType SCD30_getSerialNumber(I2C_HandleTypeDef* i2cHandle, SCD30DescriptorType * desr);


uint16_t SCD30_readRegister(I2C_HandleTypeDef* i2cHandle, uint16_t registerAddress);





/* USER CODE BEGIN Private defines */
//THe default I2C address for the SCD30 is 0x61, shifted to left results in 0XC2
#define SCD30_BASE_ADDR 												0xC2
		
//Available commands		
#define CMD_CONTINUOUS_MEASUREMENT  						0x0010
#define CMD_SET_MEASUREMENT_INTERVAL 						0x4600
#define CMD_GET_DATA_READY 											0x0202
#define CMD_READ_MEASUREMENT 										0x0300
#define CMD_AUTOMATIC_SELF_CALIBRATION 					0x5306
#define CMD_SET_FORCED_RECALIBRATION_FACTOR 		0x5204
#define CMD_SET_TEMPERATURE_OFFSET 							0x5403
#define CMD_SET_ALTITUDE_COMPENSATION 					0x5102
#define CMD_READ_SERIALNBR 											0xD033

#define SCD30_POLYNOMIAL                        0x131   // P(x) = x^8 + x^5 + x^4 + 1 = 100110001
#define SCD30_CRC_INIT                          0xff
            
#define SCD30_SN_SIZE                           33      //size of the s/n ascii string + CRC values
 

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __DRVSCD30_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
