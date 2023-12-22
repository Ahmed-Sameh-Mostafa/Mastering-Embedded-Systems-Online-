/*
 * I2C.c
 *
 * Created: 22/12/2023 16:56:17
 *  Author: Lenovo
 */ 

#include "I2C.h"


#undef F_CPU 
#define F_CPU 8000000UL

void I2C_Init(unsigned long SCL_Clock)
{
	TWBR = (unsigned char)(((F_CPU / SCL_Clock) - 16 ) /( 2 * I2C_Prescaler));
	if(I2C_Prescaler == 1)
		TWSR = 0;
	else if (I2C_Prescaler == 4)
		TWSR = 1;
	else if (I2C_Prescaler == 16)
		TWSR = 2;
	else if (I2C_Prescaler == 64)
		TWSR = 3;
}

void I2C_Start(void)
{
	TWCR  = (1<<TWINT) | (1 << TWEN) | (1<<TWSTA);
	while(((TWCR & (1<<7)) == 0));
	while((TWSR) != 0x08);
}

void I2C_Write(unsigned char data)
{
	TWDR = data;
	TWCR = (1<<TWINT) | (1 << TWEN);
	while((TWCR & 0x80) == 0);
}

unsigned char I2C_Read(unsigned char ack)
{
	
	TWCR = (1<<TWINT) | (1 << TWEN) | (ack << TWEA);
	while((TWCR & 0x80) == 0);
	
	return TWDR;
}

void I2C_Stop(void)
{
	TWCR = (1<<TWINT) | (1 << TWEN) | (1<<TWSTO);
}