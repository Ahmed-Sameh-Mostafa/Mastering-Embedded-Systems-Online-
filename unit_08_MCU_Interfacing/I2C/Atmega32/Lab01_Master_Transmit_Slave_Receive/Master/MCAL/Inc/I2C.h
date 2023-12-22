/*
 * I2C.h
 *
 * Created: 22/12/2023 16:56:34
 *  Author: Lenovo
 */ 

#ifndef I2C_H_
#define I2C_H_

#include "AvrMemoryMap.h"

// Master transmit

// TWCR
#define TWIE					0
#define TWEN					2
#define TWWC					3
#define TWSTO					4
#define TWSTA					5
#define TWEA					6
#define TWINT					7



#define I2C_Prescaler			1			//values can be 1, 4, 16, 64
/******************************************I2C API**********************************************/
void I2C_Init(unsigned long SCL_Clock);

void I2C_Start(void);

void I2C_Write(unsigned char data);

void I2C_Stop(void);

#endif /* I2C_H_ */