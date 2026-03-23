/*
 * MPU.h
 *
 *  Created on: Jun 18, 2023
 *      Author:
 */

#ifndef INC_MPU_H_
#define INC_MPU_H_
#include "stm32f4xx_hal.h"

void MPU6050_Init (void);

void MPU6050_Read_Accel (void);

void MPU6050_Read_Gyro (void);


#endif /* INC_MPU_H_ */
