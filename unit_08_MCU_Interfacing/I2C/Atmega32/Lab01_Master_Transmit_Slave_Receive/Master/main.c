 /*
 * Task_02.c
 *
 * Created: 21/12/2023 00:42:11
 * Author : Lenovo
 */ 

#include "AvrMemoryMap.h"
#include "GPIO.h"
#include "I2C.h"
#include<util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#define F_CPU 8000000UL

int main(void)
{
	unsigned char ch = 0;
	I2C_Init(0x48);
	while(1)
	{
		_delay_ms(500);
		I2C_Start();
		I2C_Write(0b11010000 + 0); 
		while((TWSR) != 0x18);
		I2C_Write(ch++);
		while((TWSR) != 0x28);
		I2C_Stop();
	}
	
   
	return 0;
}
