/*
 * ADC.h
 *
 * Created: 24/12/2023 23:20:35
 *  Author: Lenovo
 */ 


#ifndef ADC_H_
#define ADC_H_

/******************************************************************************
*                               INCLUDES			                          *
*******************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Types.h"
#include "Utils.h"

/******************************************************************************
*									ENUMS	                				  *
*******************************************************************************/

typedef enum
{
	ADC_REF_AREF = 0x00,
	ADC_REF_AVCC = 0x40,
	ADC_REF_256 = 0xC0
}ADC_Volt_Ref;



typedef enum
{
	ADC_SingleEnded_Ch0 = 0x00,
	ADC_SingleEnded_Ch1 = 0x01,
	ADC_SingleEnded_Ch2 = 0x02,
	ADC_SingleEnded_Ch3 = 0x03,
	ADC_SingleEnded_Ch4 = 0x04,
	ADC_SingleEnded_Ch5 = 0x05,
	ADC_SingleEnded_Ch6 = 0x06,
	ADC_SingleEnded_Ch7 = 0x07,
}ADC_SingleEndedChannel;

typedef enum
{
	ADC_Prescaler_1		= 0x00,
	ADC_Prescaler_2		= 0x01,
	ADC_Prescaler_4		= 0x02,
	ADC_Prescaler_8		= 0x03,
	ADC_Prescaler_16	= 0x04,
	ADC_Prescaler_32	= 0x05,
	ADC_Prescaler_64	= 0x06,
	ADC_Prescaler_128	= 0x07,
}ADC_Prescaler;


typedef enum
{
	ADC_Trigger_FreeRunning = 0x00,
	ADC_Trigger_Comparator = 0x20,
	ADC_Trigger_External_interrupt= 0x40,
	ADC_Trigger_timer0_compareMatch = 0x60,
	ADC_Trigger_timer0_overflow = 0x80,
	ADC_Trigger_timer1_compareMatchB = 0xA0,
	ADC_Trigger_timer1_overflow = 0xC0,
	ADC_Trigger_timer1_captureEvent = 0xE0
}ADC_AutoTriggerSource;

typedef enum
{
	ADC_Interrupt_DISABLE = 0x00,
	ADC_Interrupt_Enable = 0x08,
}ADC_Interrupt;


/******************************************************************************
*									STRUCT	                				  *
*******************************************************************************/
typedef struct
{
	ADC_Volt_Ref ref;
	ADC_SingleEndedChannel channel;
	ADC_Prescaler prescaler;
	ADC_AutoTriggerSource triggerSource;
	ADC_Interrupt adc_interrupt;
	
}ST_ADC_CONFIG;

/******************************************************************************
*									APIS				                      *
*******************************************************************************/

void ADC_Init(ST_ADC_CONFIG* config);

uint16_t ADC_Read_Blocking(void);
uint16_t ADC_Read_NoBlocking(void);

void ADC_start_conversion(ADC_SingleEndedChannel ch);

void ADC_SetCallBack_Interrupt(PTR_VoidFuncVoid_t callback);

#endif /* ADC_H_ */