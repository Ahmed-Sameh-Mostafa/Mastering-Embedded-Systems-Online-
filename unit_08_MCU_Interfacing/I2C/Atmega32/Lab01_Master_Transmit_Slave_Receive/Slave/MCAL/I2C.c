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

unsigned char I2C_Read(unsigned char ack)
{
	unsigned char x = 0;
	TWCR = (1<<TWINT) | (1<<TWEN) | (ack<< TWEA);
	while((TWCR & 1<<7) == 0);
	while((TWSR) != 0x60) x = TWSR;
	TWCR = (1<<TWINT) | (1<<TWEN) | (ack<< TWEA);
	while((TWCR & 1<<7) == 0);
	while((TWSR) != 0x80) x = TWSR;
	
	return TWDR;
}