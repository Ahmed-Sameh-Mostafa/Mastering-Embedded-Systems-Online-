/*
 * Keypad.c
 *
 *  Created on: Oct 28, 2021
 *      Author: Mostafa Mahmoud Elshiekh
 */



#include "Keypad.h"

static uint16_t Key_padRow[] = Keypad_rows; //rows of the keypad
static uint16_t Key_padCol[] = Keypad_cols; //columns

static uint8_t Key_pad_keys[Keypad_rows_no][Keypad_cols_no] = Keypad_keys;

static uint16_t rows_mask = 0;
static uint16_t cols_mask = 0;

void keypad_Init(void)
{

	GPIO_PinConfig_t PinCinfg;

	// Initialising rows as inputs
	PinCinfg.GPIO_MODE = GPIO_MODE_INPUT_PU;
	for(int r = 0; r < Keypad_rows_no; r++)
	{
		PinCinfg.GPIO_PinNumber = Key_padRow[r];
		MCAL_GPIO_Init(KEYPAD_PORT, &PinCinfg);
		rows_mask |= Key_padRow[r];
	}

	//	Initialising columns as output
	PinCinfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCinfg.GPIO_OUTPUT_Speed = GPIO_SPEED_10M;

	for(int c = 0; c < Keypad_cols_no; c++)
	{
		PinCinfg.GPIO_PinNumber = Key_padCol[c];
		MCAL_GPIO_Init(KEYPAD_PORT, &PinCinfg);
		cols_mask |= Key_padCol[c];
	}

}

uint8_t keypad_Read(void)
{
	uint16_t r,c;
	for (c = 0; c < Keypad_cols_no; c++)
	{
		MCAL_GPIO_WritePort(KEYPAD_PORT, Key_padCol[c]);
		for(r = 0; r < Keypad_rows_no; r++)
		{
			if ( MCAL_GPIO_ReadPin(KEYPAD_PORT, Key_padRow[r]) )
			{
				while(MCAL_GPIO_ReadPin(KEYPAD_PORT, Key_padRow[r]));
				return Key_pad_keys[r][c];
			}
		}
	}


	return 'N';
}


