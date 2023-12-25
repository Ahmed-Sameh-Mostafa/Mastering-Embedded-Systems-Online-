/*
 * lcd.c
 *
 * Created: 27/08/2023 23:49:32
 *  Author: Lenovo
 */ 
#include "lcd.h"
#include <stdlib.h>

void LCD_INIT()
{
	/* important note: there are two methods to initialize the lcd 
	one is the standard and the only way to work it the internal reset circuit doesn't work well
	the second method is the methods implemented here and it works only if the internel reset circuit worked well */
	_delay_ms(20);
	LCD_check_lcd_isbusy();
	DataDir_LCD_CTRL |= (1<<EN_SWITCH | 1<<RW_SWITCH | 1<<RS_SWITCH) ;
	LCD_CTRL &= ~(1<<EN_SWITCH | 1<<RW_SWITCH | 1<<RS_SWITCH) ;

	DataDir_LCD_PORT = 0xff ;
	_delay_ms(15); 
	LCD_clear_screen();
	
	#ifdef EIGHT_BIT_MODE
	LCD_WRITE_COMMAND(LCD_FUNCTION_8BIT_2LINES);
	#endif
	#ifdef FOUR_BIT_MODE
	LCD_WRITE_COMMAND(0x02);
	LCD_WRITE_COMMAND(LCD_FUNCTION_4BIT_2LINES);
	#endif
	
	LCD_WRITE_COMMAND(LCD_ENTRY_MODE);
	LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW);
	LCD_WRITE_COMMAND(LCD_DISP_ON_CURSOR_BLINK);
}
void LCD_WRITE_COMMAND(unsigned char command)
{
	#ifdef EIGHT_BIT_MODE
	LCD_check_lcd_isbusy();
	LCD_PORT = command;
	LCD_CTRL &= ~((1 << RS_SWITCH) | (1<<RW_SWITCH));
	_delay_ms(3);
	LCD_lcd_kick();
	#endif
	// in four bit mode the command is sent on 2 pulses and that is why u will see 2 kicks
	#ifdef FOUR_BIT_MODE
	//LCD_check_lcd_isbusy();
	LCD_PORT = (LCD_PORT & 0x0F) | (command & 0xF0);
	LCD_CTRL &= ~ ((1<<RW_SWITCH)|(1<<RS_SWITCH));
	_delay_ms(3);
	LCD_lcd_kick ();
	LCD_PORT = (LCD_PORT & 0x0F) | (command << DATA_shift);
	LCD_CTRL &= ~ ((1<<RW_SWITCH)|(1<<RS_SWITCH));
	_delay_ms(3);
	LCD_lcd_kick();
	#endif
}
void LCD_WRITE_CHAR(unsigned char character)
{
	#ifdef EIGHT_BIT_MODE
	LCD_check_lcd_isbusy();
	LCD_PORT = character;
	LCD_CTRL &= ~ (1<<RW_SWITCH);
	LCD_CTRL |= (1<<RS_SWITCH);
	_delay_ms(3);
	LCD_lcd_kick();
	#endif
	// in four bit mode the command is sent on 2 pulses and that is why u will see 2 kicks
	#ifdef FOUR_BIT_MODE
	//LCD_check_lcd_isbusy();
	LCD_PORT = (LCD_PORT & 0x0F) | (character & 0xF0);
	LCD_CTRL |= (1<<RS_SWITCH);
	LCD_CTRL &= ~ (1<<RW_SWITCH);
	_delay_ms(3);
	LCD_lcd_kick ();
	LCD_PORT = (LCD_PORT & 0x0F) | (character << 4);
	LCD_CTRL |= (1<<RS_SWITCH);
	LCD_CTRL &= ~ (1<<RW_SWITCH);
	_delay_ms(3);
	LCD_lcd_kick();
	#endif
}
void LCD_WRITE_STRING(char* string)
{
	int count = 0;
	while (*string > 0){
		count++;
		LCD_WRITE_CHAR(*string++);
		if (count == 16)
		{
			LCD_GOTO_XY(2,0);
		}
		else if (count == 32)
		{
			LCD_clear_screen();
			LCD_GOTO_XY(1,0);
			count = 0;
		}
	}
}
void LCD_check_lcd_isbusy(void)
{
	/* to check if an lcd is busy we need to read from lcd so we 
	1.change the port to input.
	2.turn on read/write pin(read mode).
	3. turn off 
		RS which is Register selector: 
			0: Instruction register (for write) Busy flag:
			address counter (for read)
			1: Data register (for write and read)
	wait for approx. 50 ms after turning on enable signal
	turn enable signal
	enable is used for starting a read/ write operation
	*/
	DataDir_LCD_PORT = 0x00;
	LCD_CTRL |= (1<< RW_SWITCH);
	LCD_CTRL &= ~(1<<RS_SWITCH);
	LCD_lcd_kick();
	DataDir_LCD_PORT = 0xFF;
	LCD_CTRL &= ~(1<< RW_SWITCH);
}
void LCD_lcd_kick(void)
{
	/* this method works as a pulse generator for the enable signal
	as in the rising edge of the signal the lcd read the command and in the falling edge it executes the command */ 
	LCD_CTRL &= ~(1<<EN_SWITCH);
	_delay_ms(50);
	LCD_CTRL |= (1<<EN_SWITCH);
}
void LCD_clear_screen()
{
	LCD_WRITE_COMMAND(LCD_CLEAR_SCREEN);
}
void LCD_GOTO_XY(unsigned char line, unsigned char position)
{
	if (line == 1)
	{
		if (position < 16 && position >= 0)
		{
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW+position);
		}
	}
	if (line == 2)
	{
		if (position < 16 && position >= 0)
		{
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_SECOND_ROW+position);
		}
	}
}


void LCD_WriteNumber(unsigned long x)
{
	char str[20];
	itoa(x,str, 10);
	LCD_WRITE_STRING(str);
}
