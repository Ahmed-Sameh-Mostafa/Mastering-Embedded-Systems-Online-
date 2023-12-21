/*
 * Task_02.c
 *
 * Created: 09/09/2023 00:42:11
 * Author : Lenovo
 */ 

#include "AvrMemoryMap.h"
#include "GPIO.h"
#include "HAL/LCD_Driver/lcd.h"
#include "UART.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#define F_CPU 8000000UL

int main(void)
{
    /* Replace with your application code */
	/*unsigned long x = 8 + '0';
	unsigned char str[100];
	LCD_INIT();
	UART_Init();
	//LCD_WRITE_STRING("Uart TR ");
	UART_Send('M');
	UART_Send(' ');
	UART_Send_String("Learn-in-depth");
	UART_Send_Int32(x);
	x = UART_Receive_Int32();
	LCD_WRITE_CHAR((unsigned char)x);
	UART_Receive_String(str);
	LCD_WRITE_STRING(str);
	
	*/
	
	/**********************************Common code*******************************/
	unsigned char str[100];
	unsigned char x = 0, y = 0;
	sei();
	LCD_INIT();
	UART_Init();
	
	/***************************************3 - Part 1***********************************/
	/*
	LCD_WRITE_STRING("Part 1");
	UART_SendStringAsynch("Ahmed");
	UART_SendStringAsynch(" Sameh");
	*/
	/***************************************3 - Part 2***********************************/
	/*
	_delay_ms(1000);
	LCD_GOTO_XY(2,0);
	LCD_WRITE_STRING("Part 2");
	UART_SendStringAsynch("\rAhmed");
	_delay_ms(1000);
	UART_SendStringAsynch(" Sameh");
	*/
	
	/*******************************************4****************************************/
	unsigned char *ptr = (void*)0;
	UART_RecvStringAsynch(str, &ptr);
	
    while (1) 
    {
		/********************************************1******************************/
		/*
		LCD_GOTO_XY(2,0);
		UART_Receive_String(str);
		LCD_WRITE_STRING(str);
		LCD_WRITE_STRING("                       ");
		
		LCD_GOTO_XY(1,0);
		LCD_WriteNumber(x);
		x++;
		if(x == 10)
		{
			x=0;
		}
		_delay_ms(200);
		*/
		
		/*****************************2***********************/
		
		/*if(UART_Receive_PerodicCheck(&y))
		{
			LCD_GOTO_XY(1,0);
			LCD_WRITE_CHAR(y);
		}
		
		LCD_GOTO_XY(2,0);
		LCD_WriteNumber(x);
		x++;
		if(x == 10)
		{
			x=0;
		}
		_delay_ms(200);
		*/
		
		
		/************************************4*********************************/
		
		if(*ptr)
		{
			LCD_clear_screen();
			LCD_GOTO_XY(1,0);
			LCD_WRITE_STRING(str);
		}
		
		LCD_GOTO_XY(2,0);
		LCD_WriteNumber(x);
		x++;
		if(x == 10)
		{
			x=0;
		}
		_delay_ms(200);
		
		
    }
	return 0;
}
