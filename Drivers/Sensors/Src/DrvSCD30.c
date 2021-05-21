/**
  ******************************************************************************
  * @file    DrvSCD30.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
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
#include "DrvSCD30.h"

#include "stm32f4xx_hal_def.h"


/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

struct __SCD30Descriptor
{
  uint16_t co2m;          /*!< High order 16 bit word of CO2 */
  uint16_t co2l;          /*!< Low  order 16 bit word of CO2 */
  uint16_t tempm;         /*!< High order 16 bit word of Temp */
  uint16_t templ;         /*!< Low order 16 bit word of Temp */
  uint16_t humm;          /*!< High order 16 bit word of Hum */
  uint16_t huml;          /*!< Low order 16 bit word of Hum */

  uint16_t ready;         /*!< 1 = ready, 0 = busy */

  uint32_t co2i;          /*!< 32 bit int of CO2 */
  uint32_t tempi;         /*!< 32 bit int of Temp */
  uint32_t humi;          /*!< 32 bit int of Hum */

  float co2f;             /*!< float of CO2 concentration */
  float tempf;            /*!< float of Temp */
  float humf;             /*!< float of Hum */

  uint16_t acode;         /*!< Article code number?? */
  uint8_t sn[24];         /*!< ASCII Serial Number */
};

static SCD30DescriptorType SCD30descr;


uint16_t SCD30_readRegister(I2C_HandleTypeDef* i2cHandle, uint16_t registerAddress){
	
	int returnValue = 0;
	
	uint8_t regAddr[2];
	// uint8_t receive_buffer[18] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint8_t receive_buffer[2] = {0,0};
	
	regAddr[1] = (0xFFu & registerAddress);
	regAddr[0] = (0xFFu & (registerAddress >> 8));
	
	// set the register pointer to the register wanted to read 
	
	if(HAL_I2C_Master_Transmit(i2cHandle, SCD30_BASE_ADDR, regAddr, 2 , 150) != 0x00U){
		return returnValue = -1;
	}else{
		// receive the n x 8bit data into the receive_buffer
		HAL_I2C_Master_Receive(i2cHandle, SCD30_BASE_ADDR, receive_buffer, sizeof(receive_buffer)/sizeof(receive_buffer[0]), 150);
		

		return returnValue = ((uint8_t)receive_buffer[1] << 8 | receive_buffer[0]);
	}

}

uint8_t SCD30_calcCrc2b(uint16_t seed)
{
  uint8_t bit;                  // bit mask
  uint8_t crc = SCD30_CRC_INIT; // calculated checksum
  
  // calculates 8-Bit checksum with given polynomial
  crc ^= (seed >> 8) & 255;
  for(bit = 8; bit > 0; --bit)
  {
    if(crc & 0x80) crc = (crc << 1) ^ SCD30_POLYNOMIAL;
    else           crc = (crc << 1);
  }

  crc ^= seed & 255;
  for(bit = 8; bit > 0; --bit)
  {
    if(crc & 0x80) crc = (crc << 1) ^ SCD30_POLYNOMIAL;
    else           crc = (crc << 1);
  }
  
  return crc;  
}

SCD30ErrCodeType SCD30init(SCD30HandleType * ptr2Handle){
  SCD30HandleType const SCD30Handle = &SCD30descr;
  
  *ptr2Handle = SCD30Handle;
  
  
  return SCDnoERROR;
  
}

SCD30ErrCodeType SCD30_checkCrc2b(uint16_t seed, uint8_t crcIn)
{
  uint8_t crcCalc = SCD30_calcCrc2b(seed);
  if(crcCalc != crcIn) return SCDcrcERROR;
  return SCDnoERROR;
}


SCD30ErrCodeType SCD30_getSerialNumber(I2C_HandleTypeDef* i2cHandle, SCD30HandleType  SCD30_Handle)
{
  uint8_t i2cBuffer[64];
  uint8_t regAddr[2];
  HAL_StatusTypeDef respErrValue;
  
  regAddr[0] = (0xFFu & (CMD_READ_SERIALNBR >> 8));
  regAddr[1] = (0xFFu & CMD_READ_SERIALNBR);  
  
  respErrValue = HAL_I2C_Master_Transmit(i2cHandle, SCD30_BASE_ADDR, regAddr, 2, 150);
  
  if(respErrValue == HAL_ERROR){
    return SCDnoAckERROR;
  }else if(respErrValue == HAL_TIMEOUT){
    return SCDtimeoutERROR;
  }
  
  int i = 0;
  for(i = 0; i < sizeof(SCD30_Handle->sn)/sizeof(SCD30_Handle->sn[0]); i++){
    SCD30_Handle->sn[i] = 0;
  }
  for(i = 0; i < sizeof(i2cBuffer)/sizeof(i2cBuffer[0]); i++){
    i2cBuffer[i] = 0;
  }
  
  respErrValue = HAL_I2C_Master_Receive(i2cHandle, SCD30_BASE_ADDR, i2cBuffer, SCD30_SN_SIZE, 150);
  
  if(respErrValue == HAL_ERROR){
    return SCDnoAckERROR;
  }else if(respErrValue == HAL_TIMEOUT){
    return SCDtimeoutERROR;
  }
  
  int t = 0;
  for(int i = 0; i < SCD30_SN_SIZE; i += 3){
    uint16_t stat = (i2cBuffer[i] << 8) | i2cBuffer[i+1];
    SCD30_Handle->sn[i - t] = stat >> 8;
    SCD30_Handle->sn[i - t + 1] = stat & 0xFFu;
    uint8_t dat = SCD30_checkCrc2b(stat, i2cBuffer[i + 2]);
    t++;
    if(dat == SCDcrcERROR) return SCDcrcERRORv1;
    if(stat == 0) break;    
  }
  
  
  return SCDnoERROR;
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
