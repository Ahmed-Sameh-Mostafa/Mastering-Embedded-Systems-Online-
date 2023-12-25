/*
 * Timer.h
 *
 * Created: 24/12/2023 17:01:30
 *  Author: Lenovo
 */ 


#ifndef TIMER_PWM_H_
#define TIMER_PWM_H_

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
	NORMAL,
	PWM_Phase_Correct_Inverting = 0x70,
	PWM_Phase_Correct_NonInverting = 0x60,
	CTC = 0x08,
	PWM_FAST_Inverting = 0x78,
	PWM_FAST_NonInverting = 0x68,
}TIMER0_MODE_t;

typedef enum
{
	OCIE_DISABLE = 0x00,
	OCIE_ENABLE = 0x02
}OCMIE0_t;

typedef enum
{
	TOIE_DISABLE = 0x00,
	TOIE_ENABLE = 0x01
}TOVFIE0_t;

typedef enum
{
	NO_CLK_SRC,
	NO_PRESCALING,
	PRESCALING_CLK8,
	PRESCALING_CLK64,
	PRESCALING_CLK256,
	PRESCALING_CLK1024,
	EXT_CLK_FALLING,
	EXT_CLK_RISING,
}TIMER0_CLOCK_t;

/******************************************************************************
*									STRUCT	                				  *
*******************************************************************************/
typedef struct
{
	TIMER0_MODE_t mode;
	OCMIE0_t  ocmInterrupt;
	TOVFIE0_t ovfInterrupt;
	TIMER0_CLOCK_t clk;
}STIMER0_CONFIG;

/******************************************************************************
*									APIS				                      *
*******************************************************************************/
E_STATUS_t TIMER0_Init(STIMER0_CONFIG* configuartion);
E_STATUS_t TIMER0_Stop();

E_STATUS_t TIMER0_GetCompareValue(ptr_uint8_t pu8_TicksNumber);
E_STATUS_t TIMER0_SetCompareValue(uint8_t u8_TicksNumber);

E_STATUS_t TIMER0_GetCounterValue(ptr_uint8_t pu8_TicksNumber);
E_STATUS_t TIMER0_SetCounterValue(uint8_t u8_TicksNumber);

E_STATUS_t TIMER0_GetOverflowValue(ptr_uint8_t pu8_TicksNumber);
E_STATUS_t TIMER0_SetOverflowValue(uint8_t u8_TicksNumber);

void TIMER0_CALLBACK_Overflow_INTERRUPT(PTR_VoidFuncVoid_t callback);
void TIMER0_CALLBACK_CompareMatch_INTERRUPT(PTR_VoidFuncVoid_t callback);




#endif /* TIMER_H_ */