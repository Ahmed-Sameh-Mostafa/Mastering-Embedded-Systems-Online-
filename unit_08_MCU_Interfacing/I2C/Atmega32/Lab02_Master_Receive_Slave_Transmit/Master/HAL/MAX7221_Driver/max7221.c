/*
 * max7221.c
 *
 * Created: 21/12/2023 23:58:22
 *  Author: Lenovo
 */ 

#include "max7221.h"

void HAL_MAX7221_EXECUTE(unsigned char address, unsigned char value)
{
	PORTB &= ~(1<<SS);
	SPI_SendReceive(address);
	SPI_SendReceive(value);
	PORTB |= (1<<SS);
}
