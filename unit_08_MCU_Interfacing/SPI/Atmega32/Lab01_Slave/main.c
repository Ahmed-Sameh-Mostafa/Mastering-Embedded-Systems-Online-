 /*
 * Task_02.c
 *
 * Created: 21/12/2023 00:42:11
 * Author : Lenovo
 */ 

#include "AvrMemoryMap.h"
#include "GPIO.h"
#include "HAL/LCD_Driver/lcd.h"
#include "SPI.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#define F_CPU 1000000UL

int main(void)
{
	unsigned char ch = 0;
	Port_Direction(portA, output);
	SPI_Init();
	
	while(1)
	{
		for(ch = 0; ch <=255; ch++)
		{
			_delay_ms(1000);
			PORTA = SPI_SendReceive(ch);
		}
		
	}
	
   
	return 0;
}
