/*
 * lcd.c
 *
 * Created: 27/08/2023 23:49:32
 *  Author: Lenovo
 */ 
#include "lcd.h"

GPIO_PinConfig_t PinCfg;

void wait_ms(uint32_t time)
{
	uint32_t i,j;
	for(i = 0; i < time; i++)
		for(j = 0; j < 255; j++);
}

void LCD_INIT()
{
	/* important note: there are two methods to initialize the lcd 
	one is the standard and the only way to work it the internal reset circuit doesn't work well
	the second method is the methods implemented here and it works only if the internel reset circuit worked well */
	wait_ms(20);

	//EN, RS, RW input

	//EN
	PinCfg.GPIO_PinNumber = EN_SWITCH;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	//RS
	PinCfg.GPIO_PinNumber = RS_SWITCH;
//	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	//RW
	PinCfg.GPIO_PinNumber = RW_SWITCH;
//	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

//	wait_ms(15);

	/*          Data pin output 		*/
	//PA0 output push pull
	PinCfg.GPIO_PinNumber = GPIO_PIN_0;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

		//PA1 output push pull
	PinCfg.GPIO_PinNumber = GPIO_PIN_1;
//	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
//	PinCfg.GPIO_OUTPUT_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	//PA2 output push pull
	PinCfg.GPIO_PinNumber = GPIO_PIN_2;
//	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
//	PinCfg.GPIO_OUTPUT_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	//PA3 output push pull
	PinCfg.GPIO_PinNumber = GPIO_PIN_3;
//	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
//	PinCfg.GPIO_OUTPUT_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);


	//PA4 output push pull
	PinCfg.GPIO_PinNumber = GPIO_PIN_4;
//	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
//	PinCfg.GPIO_OUTPUT_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	//PA5 output push pull
	PinCfg.GPIO_PinNumber = GPIO_PIN_5;
//	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
//	PinCfg.GPIO_OUTPUT_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	//PA6 output push pull
	PinCfg.GPIO_PinNumber = GPIO_PIN_6;
//	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
//	PinCfg.GPIO_OUTPUT_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	//PA7 output push pull
	PinCfg.GPIO_PinNumber = GPIO_PIN_7;
//	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
//	PinCfg.GPIO_OUTPUT_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	MCAL_GPIO_WritePin(LCD_CTRL, EN_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);

	wait_ms(15);

	LCD_clear_screen();
	
//	#ifdef EIGHT_BIT_MODE
	LCD_WRITE_COMMAND(LCD_FUNCTION_8BIT_2LINES);
//	#endif
//	#ifdef FOUR_BIT_MODE
//	LCD_WRITE_COMMAND(0x02);
//	LCD_WRITE_COMMAND(LCD_FUNCTION_4BIT_2LINES);
//	#endif
	
	LCD_WRITE_COMMAND(LCD_ENTRY_MODE);
	LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW);
	LCD_WRITE_COMMAND(LCD_DISP_ON_CURSOR_BLINK);
}
void LCD_WRITE_COMMAND(unsigned char command)
{
//	#ifdef EIGHT_BIT_MODE
//	LCD_check_lcd_isbusy();
//	LCD_PORT = command;
	MCAL_GPIO_WritePort(LCD_PORT, command);
//	LCD_CTRL &= ~((1 << RS_SWITCH) | (1<<RW_SWITCH));
	MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);

	wait_ms(1);
	LCD_lcd_kick();
//	#endif
	// in four bit mode the command is sent on 2 pulses and that is why u will see 2 kicks
//	#ifdef FOUR_BIT_MODE
//	LCD_check_lcd_isbusy();
//	LCD_PORT = (LCD_PORT & 0x0F) | (command & 0xF0);
//	LCD_CTRL &= ~ ((1<<RW_SWITCH)|(1<<RS_SWITCH));
//	LCD_lcd_kick ();
//	LCD_PORT = (LCD_PORT & 0x0F) | (command << 4);
//	LCD_CTRL &= ~ ((1<<RW_SWITCH)|(1<<RS_SWITCH));
//	LCD_lcd_kick();
//	#endif
}
void LCD_WRITE_CHAR(unsigned char character)
{
//	#ifdef EIGHT_BIT_MODE
//	LCD_check_lcd_isbusy();
//	LCD_PORT = character;
	MCAL_GPIO_WritePort(LCD_CTRL, character);
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_SET);
	wait_ms(1);
	LCD_lcd_kick();
//	#endif
	// in four bit mode the command is sent on 2 pulses and that is why u will see 2 kicks
//	#ifdef FOUR_BIT_MODE
//	LCD_check_lcd_isbusy();
//	LCD_PORT = (LCD_PORT & 0x0F) | (character & 0xF0);
//	LCD_CTRL &= ~ (1<<RW_SWITCH);
//	LCD_CTRL |= (1<<RS_SWITCH);
//	LCD_lcd_kick ();
//	LCD_PORT = (LCD_PORT & 0x0F) | (character << 4);
//	LCD_CTRL &= ~ (1<<RW_SWITCH);
//	LCD_CTRL |= (1<<RS_SWITCH);
//	LCD_lcd_kick();
//	#endif
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
	/*          Data pin output 		*/

	//PA0 input floating
	PinCfg.GPIO_PinNumber = GPIO_PIN_0;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);


	//PA1 input floating
	PinCfg.GPIO_PinNumber = GPIO_PIN_1;
//	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	//PA2 input floating
	PinCfg.GPIO_PinNumber = GPIO_PIN_2;
//	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	//PA3 input floating
	PinCfg.GPIO_PinNumber = GPIO_PIN_3;
//	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);


	//PA4 input floating
	PinCfg.GPIO_PinNumber = GPIO_PIN_4;
//	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	//PA5 input floating
	PinCfg.GPIO_PinNumber = GPIO_PIN_5;
//	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	//PA6 input floating
	PinCfg.GPIO_PinNumber = GPIO_PIN_6;
//	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	//PA7 input floating
	PinCfg.GPIO_PinNumber = GPIO_PIN_7;
//	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);


	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_SET);
	MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET);

	LCD_lcd_kick();
//	DataDir_LCD_PORT |= (LCD_PORT<< DATA_shift);
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
}
void LCD_lcd_kick(void)
{
	/* this method works as a pulse generator for the enable signal
	as in the rising edge of the signal the lcd read the command and in the falling edge it executes the command */ 
	MCAL_GPIO_WritePin(LCD_CTRL, EN_SWITCH, GPIO_PIN_SET);
	wait_ms(50);
	MCAL_GPIO_WritePin(LCD_CTRL, EN_SWITCH, GPIO_PIN_RESET);
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
