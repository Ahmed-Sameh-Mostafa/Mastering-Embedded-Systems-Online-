 /*
 * Task_02.c
 *
 * Created: 21/12/2023 00:42:11
 * Author : Lenovo
 */ 

#include "AvrMemoryMap.h"
#include "GPIO.h"
#include "HAL/LCD_Driver/lcd.h"
#include "HAL/MAX7221_Driver/max7221.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#define F_CPU 1000000UL

int main(void)
{
	unsigned char counter = 0;
	unsigned char index_display = 1;
	SPI_Init();
	HAL_MAX7221_EXECUTE(ADD_DECODE, VALUE_DECODE_0_TO_7);
	HAL_MAX7221_EXECUTE(ADD_SCAN_LIMIT, VALUE_SCAN_LIMIT_0_TO_7);
	HAL_MAX7221_EXECUTE(ADD_INTENSITY, VALUE_INTENSITY_MAX);
	HAL_MAX7221_EXECUTE(ADD_SHUTDOWN, VALUE_DISPLAY_ON);
	
	while(1)
	{
		for(index_display = 1; index_display < 9; index_display++)
		{
			HAL_MAX7221_EXECUTE(index_display, counter++);
			_delay_ms(200);
		}
	}
	
   
	return 0;
}
