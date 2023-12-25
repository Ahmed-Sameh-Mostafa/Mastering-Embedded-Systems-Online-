/*
 * SPI.c
 *
 * Created: 21/12/2023 21:39:42
 *  Author: Lenovo
 */ 

#include "SPI.h"
#include "GPIO.h"

void SPI_Init(void)
{
	#if (SPI_MODE == MASTER)
		SPCR |= (1<<MSTR);
		SPCR &= ~(1<<CPOL);
		Pin_Direction(portB, SS,output);
		Pin_Direction(portB, MOSI,output);
		Pin_Direction(portB, SCK,output);
		Pin_Direction(portB, MISO,input);
	#elif (SPI_MODE == SLAVE)
		SPCR &= ~(1<<MSTR);
		Pin_Direction(portB, SS,input);
		Pin_Direction(portB, MOSI,input);
		Pin_Direction(portB, SCK,input);
		Pin_Direction(portB, MISO,unsigned char output);
	#endif
	
	SPCR |= (1<<SPE);
	
}


unsigned char SPI_SendReceive(unsigned char data)
{
	SPDR = data;
	while(!((SPSR>>SPIF)&1));
	return SPDR;
}