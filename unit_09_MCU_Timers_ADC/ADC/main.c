 /*
 * Task_02.c
 *
 * Created: 21/12/2023 00:42:11
 * Author : Lenovo
 */ 
#define F_CPU 8000000UL
#include "AvrMemoryMap.h"
#include "GPIO.h"
#include "HAL/LCD_Driver/lcd.h"
#include "ADC.h"
#include "Utils.h"
#include<util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#define ADC_channel			7

int main(void)
{
	uint16_t data = 0;
	uint16_t precentage = 0;
	LCD_INIT();
	ST_ADC_CONFIG config;
	config.adc_interrupt = ADC_Interrupt_DISABLE;
	config.channel = ADC_SingleEnded_Ch7;
	config.prescaler = ADC_Prescaler_64;
	config.ref = ADC_REF_AVCC;
	config.triggerSource = ADC_Trigger_FreeRunning;
	Pin_Direction(portA, ADC_channel, input);
	ADC_Init(&config);
	
	
	
	while(1)
	{
		LCD_clear_screen();
		LCD_GOTO_XY(1,0);
		LCD_WRITE_STRING("Prec: ");
		ADC_start_conversion(ADC_SingleEnded_Ch7);
		data = ADC_Read_Blocking();
		precentage = (((uint32_t)data * 100 )/1023);
		LCD_GOTO_XY(1,7);
		//LCD_clear_screen();
		LCD_WriteNumber(precentage);
		LCD_GOTO_XY(2,0);
		uint16_t precentage_16 = (((uint32_t)precentage * 16) /100);
		for(uint16_t i = 0; i < precentage_16; i++)
		{
			LCD_WRITE_CHAR(0xFF);
		}
		//_delay_ms(250);
		
	}
	return 0;
}

