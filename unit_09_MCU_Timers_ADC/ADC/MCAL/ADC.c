/*
 * ADC.c
 *
 * Created: 24/12/2023 23:20:16
 *  Author: Lenovo
 */ 
#include "ADC.h"

/******************************************************************************
*                               GLOBAL & EXTERN VARIABLES                     *
*******************************************************************************/
PTR_VoidFuncVoid_t CALLBACK_EOC = (void *)0;

ST_ADC_CONFIG* ADC_Configurations = (void *)0;

/******************************************************************************
*								 APIS IMPLEMENTATION			              *
*******************************************************************************/

void ADC_Init(ST_ADC_CONFIG* config)
{			
	ADMUX = config->channel | config->ref;
	ADCSRA = config->adc_interrupt | config->prescaler;
	if((config->triggerSource >> 5) >= 1 && (config->triggerSource >> 5) <= 7)
	{
		SFIOR |= config->triggerSource;
		ADCSRA |= (1<<5);
	}
	else if(config->triggerSource == 0x00)
	{
		SFIOR |= config->triggerSource;
	}
	ADCSRA |= (1<<7);
	
	ADC_Configurations = config;
}

uint16_t ADC_Read_Blocking(void)
{
	while(READ_BIT(ADCSRA,ADSC));
	return ADC;
}
uint16_t ADC_Read_NoBlocking(void)
{
	return ADC;
}

void ADC_start_conversion(ADC_SingleEndedChannel ch)
{
	ADMUX &= 0xE0;
	ADMUX |= ch;
	ADCSRA |= (1<<6);
}


void ADC_SetCallBack_Interrupt(PTR_VoidFuncVoid_t callback)
{
	CALLBACK_EOC = callback;
}



ISR(ADC_vect)
{
	CALLBACK_EOC();
}