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
	
	I2C_Set_Address(0b11010000);
	while(1)
	{
		I2C_Read(1);
		I2C_Write(ch++);
	}
	
   
	return 0;
}
