/*
 * Task_02.c
 *
 * Created: 09/09/2023 00:42:11
 * Author : Lenovo
 */ 

#include "MCAL/Inc/AvrMemoryMap.h"
#include "MCAL/Inc/GPIO.h"
#include "HAL/LCD_Driver/lcd.h"
#define F_CPU 8000000UL


int main(void)
{
    /* Replace with your application code */
	Port_Direction(portA, output);
	Pin_Direction(portB, RS_SWITCH, output);
	Pin_Direction(portB, RW_SWITCH, output);
	Pin_Direction(portB, EN_SWITCH, output);
	
	LCD_INIT();
	LCD_WRITE_STRING("Learn-in-depth");
    while (1) 
    {
    }
	return 0;
}

