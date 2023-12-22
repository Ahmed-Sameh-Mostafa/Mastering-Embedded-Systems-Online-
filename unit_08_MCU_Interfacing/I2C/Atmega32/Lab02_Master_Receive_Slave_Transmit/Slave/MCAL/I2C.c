/*
 * I2C.c
 *
 * Created: 22/12/2023 16:56:17
 *  Author: Lenovo
 */ 

#include "I2C.h"


#undef F_CPU 
#define F_CPU 8000000UL


void I2C_Set_Address(unsigned char address)
{
	TWAR = address;
}


void I2C_Write(unsigned char data)
{
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while((TWCR & 0x80) == 0);
}

void I2C_Read(unsigned char ack)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (ack<< TWEA);
	while((TWCR & 0x80) == 0);
}