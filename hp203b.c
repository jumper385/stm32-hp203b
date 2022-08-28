/*
 * hp203b.c
 *
 *  Created on: 20 Aug. 2022
 *      Author: henry
 */

#include "hp203b.h"

HAL_StatusTypeDef HP203B_reset(HP203B *dev) {
	uint8_t addr = 0x06;
	if(HAL_I2C_Master_Transmit(dev->i2c, HP203B_ADDR, &addr, 1, 1000) != HAL_OK){
		return HAL_ERROR;
	}
	return HAL_OK;
}

HAL_StatusTypeDef HP203B_Init(HP203B *dev, I2C_HandleTypeDef *i2c) {
	dev->i2c = i2c;
	uint8_t addr = 0x06;
	if(HAL_I2C_Master_Transmit(dev->i2c, HP203B_ADDR, &addr, 1, 1000) != HAL_OK){
		return HAL_ERROR;
	}
	if(HAL_I2C_Master_Transmit(dev->i2c, HP203B_ADDR, (uint8_t*)0x28, 1, 1000) != HAL_OK){
		return HAL_ERROR;
	}
	return HAL_OK;
}

HAL_StatusTypeDef HP203B_getTemp(HP203B *dev) {

	uint8_t txBuffer = 0x40 | 0x00 | 0x00;

	if (HAL_I2C_Master_Transmit(dev->i2c, HP203B_ADDR, &txBuffer, 1,1000) != HAL_OK){
		return HAL_ERROR;
	}

	HAL_Delay(40);

	uint8_t rxBuffer[3];
	if(HAL_I2C_Mem_Read(dev->i2c, HP203B_ADDR, 0x32, 1, &rxBuffer, 3, 1000) != HAL_OK){
		return HAL_ERROR;
	}

	uint32_t temp_raw = rxBuffer[0] << 16 | rxBuffer[1] << 8 | rxBuffer[2];
	dev->temp = temp_raw/100.0;

	return HAL_OK;
}

HAL_StatusTypeDef HP203B_getPressure(HP203B *dev) {
	uint8_t txBuffer = 0x40 | 0x00 | 0x00;
	if (HAL_I2C_Master_Transmit(dev->i2c, HP203B_ADDR, &txBuffer, 1,1000) != HAL_OK){
		return HAL_ERROR;
	}
	uint8_t rxBuffer[3];
	if(HAL_I2C_Mem_Read(dev->i2c, HP203B_ADDR, 0x30, 1, &rxBuffer, 3, 1000) != HAL_OK){
		return HAL_ERROR;
	}

	uint32_t pressure_raw = rxBuffer[0] << 16 | rxBuffer[1] << 8 | rxBuffer[2];
	dev->pressure = pressure_raw/100.0;

	return HAL_OK;
}

HAL_StatusTypeDef HP203B_getAltitude(HP203B *dev) {
//	uint8_t txBuffer = 0x40 | 0x00 | 0x00;
//	if (HAL_I2C_Master_Transmit(dev->i2c, HP203B_ADDR, &txBuffer, 1,1000) != HAL_OK){
//		return HAL_ERROR;
//	}
	uint8_t rxBuffer[3];
	if(HAL_I2C_Mem_Read(dev->i2c, HP203B_ADDR, 0x31, 1, &rxBuffer, 3, 1000) != HAL_OK){
		return HAL_ERROR;
	}

	uint32_t alt_raw = rxBuffer[0] << 16 | rxBuffer[1] << 8 | rxBuffer[2];
	dev->altitude = alt_raw/100.0;

	return HAL_OK;
}
