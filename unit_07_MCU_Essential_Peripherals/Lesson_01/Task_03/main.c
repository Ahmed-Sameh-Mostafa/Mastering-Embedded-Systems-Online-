/*
 * Task_01.c
 *
 * Created: 26/08/2023 14:06:02
 * Author : Ahmed Sameh
 */ 

#define F_CPU 8000000UL
#include "MemMap.h"
#include "Utils.h"



void delay(unsigned int time)
{
	volatile unsigned int i, j;
	for(i = 0; i < time; i++)
		for(j = 0; j < 255; j++);
}


int main(void)
{
	// init pin D4 to be output to control the relay for controlling the buzzer
	DDRD = 0b00010000;	
    while (1) 
    {
		if((ReadBit(PIND, 0)) == 1)
		{
			SetBit(PORTD, 4);
			while((ReadBit(PIND, 0)) == 1);
		}
		ClearBit(PORTD, 4);
    }
	return 0;
}

