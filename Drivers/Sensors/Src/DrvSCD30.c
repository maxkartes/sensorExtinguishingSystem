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

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

uint16_t SCD30_readRegister(I2C_HandleTypeDef* i2cHandle, uint16_t registerAddress){
	
	uint8_t *regAddr;
	uint8_t receive_buffer[3];
	
	*regAddr = (0x00FFu & registerAddress);
	
	
	// set the register pointer to the register wanted to read 
	HAL_I2C_Master_Transmit(i2cHandle, SCD30_BASE_ADDRESS, regAddr, 1, 100);
	
	// receive the n x 8bit data into the receive_buffer
	HAL_I2C_Master_Receive(i2cHandle, SCD30_BASE_ADDRESS, receive_buffer, sizeof(receive_buffer)/sizeof(receive_buffer[0]), 100);
	

	return ((uint8_t)receive_buffer[1] << 8 | receive_buffer[0]);

}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
