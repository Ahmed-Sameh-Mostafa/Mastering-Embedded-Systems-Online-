/*
 * Task_02.c
 *
 * Created: 26/08/2023 21:13:38
 * Author : Lenovo
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
	//init port D used in this task
	//three output pins while the rest are input with high impedence
    DDRD = 0b11100000;
	unsigned int i = 5, flag = 0;
    while (1) 
    {
		if((ReadBit(PIND,0)) == 1)
		{
			if(flag == 1)
			{
				PORTD = 0x00;
				flag = 0;
				i = 5;
			}
			else
			{
				SetBit(PORTD,i);
				i++;
				if(i==8)
					flag = 1;
			}
			delay(1000);
			while((ReadBit(PIND,0)) == 1);
		}
    }
	return 0;
}

