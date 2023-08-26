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
	int i;
	//init d5, d6, d7 to be output pins
	
    while (1) 
    {
		DDRD = 0b11100000;
		for(i = 0; i < 3; i++)
		{
			SetBit(PORTD,(i+5));
			delay(1000);
		}
		for(i = 2; i >= 0; i--)
		{
			ClearBit(PORTD,(i+5));
			delay(1000);
		}	
    }
	return 0;
}

