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
	
	int returnValue = 0;
	
	uint8_t regAddr[2];
	// uint8_t receive_buffer[18] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint8_t receive_buffer[2] = {0,0};
	
	regAddr[1] = (0xFFu & registerAddress);
	regAddr[0] = (0xFFu & (registerAddress >> 8));
	
	// set the register pointer to the register wanted to read 
	
	if(HAL_I2C_Master_Transmit(i2cHandle, SCD30_BASE_ADDRESS, regAddr, 2 , 150) != 0x00U){
		return returnValue = -1;
	}else{
		// receive the n x 8bit data into the receive_buffer
		HAL_I2C_Master_Receive(i2cHandle, SCD30_BASE_ADDRESS, receive_buffer, sizeof(receive_buffer)/sizeof(receive_buffer[0]), 150);
		

		return returnValue = ((uint8_t)receive_buffer[1] << 8 | receive_buffer[0]);
	}

}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
