/*
 * hp203b.h
 *
 *  Created on: 20 Aug. 2022
 *      Author: henry
 */

#ifndef INC_HP203B_H_
#define INC_HP203B_H_

#include "stm32f1xx_hal.h"

#define HP203B_ADDR 0b1110110 << 1
#define LPF_ALPHA 0.5f

typedef struct {
	I2C_HandleTypeDef *i2c;
	float altitude;
	float temp;
	float pressure;
}HP203B;

HAL_StatusTypeDef HP203B_Init(HP203B *dev, I2C_HandleTypeDef *i2c);
HAL_StatusTypeDef HP203B_reset(HP203B *dev);
HAL_StatusTypeDef HP203B_getAltitude(HP203B *dev);
HAL_StatusTypeDef HP203B_getTemp(HP203B *dev);
HAL_StatusTypeDef HP203B_getPressure(HP203B *dev);

#endif /* INC_HP203B_H_ */
