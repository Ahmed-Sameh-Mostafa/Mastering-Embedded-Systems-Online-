/*
 * Timer.c
 *
 * Created: 24/12/2023 17:01:48
 *  Author: Lenovo
 */ 
#include "Timer_PWM.h"

/******************************************************************************
*                               GLOBAL & EXTERN VARIABLES                     *
*******************************************************************************/
PTR_VoidFuncVoid_t CALLBACK_OVF = (void *)0;
PTR_VoidFuncVoid_t CALLBACK_CM = (void *)0;
uint8_t u8_TOVNumber;
STIMER0_CONFIG* TIMER0_Configurations = (void *)0;

/******************************************************************************
*								 APIS IMPLEMENTATION			              *
*******************************************************************************/
E_STATUS_t TIMER0_Init(STIMER0_CONFIG* configuartion)
{
	E_STATUS_t u8_Retval = E_NOK;
	if (NULL_PTR == configuartion)
	{
		u8_Retval = E_NOK;
	}
	else
	{
		TIMER0_Configurations = configuartion;
		if ((NORMAL == TIMER0_Configurations->mode) || (CTC == TIMER0_Configurations->mode) || (PWM_FAST_Inverting == TIMER0_Configurations->mode) || (PWM_FAST_NonInverting == TIMER0_Configurations->mode) || (PWM_Phase_Correct_Inverting == TIMER0_Configurations->mode) || (PWM_Phase_Correct_Inverting == TIMER0_Configurations->mode))
		{
			TCCR0 |= TIMER0_Configurations->mode;
			u8_Retval = E_OK;
		}
		else
		{
			u8_Retval = E_NOK;
		}
		if ((NO_CLK_SRC <= TIMER0_Configurations->clk) && (EXT_CLK_RISING >= TIMER0_Configurations->clk))
		{
			TCCR0 |= TIMER0_Configurations->clk;
			u8_Retval = E_OK;
		}
		else
		{
			u8_Retval = E_NOK;
		}
		if ((OCIE_DISABLE == TIMER0_Configurations->ocmInterrupt) || (OCIE_ENABLE == TIMER0_Configurations->ocmInterrupt))
		{
			TIMSK |= TIMER0_Configurations->ocmInterrupt;
			u8_Retval = E_OK;
		}
		else
		{
			u8_Retval = E_NOK;
		}
		if ((TOIE_DISABLE == TIMER0_Configurations->ovfInterrupt) || (TOIE_ENABLE == TIMER0_Configurations->ovfInterrupt))
		{
			TIMSK |= TIMER0_Configurations->ovfInterrupt;
			u8_Retval = E_OK;
		}
		else
		{
			u8_Retval = E_NOK;
		}
	}
	
	return u8_Retval;
}

E_STATUS_t TIMER0_Stop()
{
	E_STATUS_t u8_Retval = E_OK;
	TIMSK |= NO_CLK_SRC;
	return u8_Retval;
}

E_STATUS_t TIMER0_GetCompareValue(ptr_uint8_t pu8_TicksNumber)
{
	E_STATUS_t u8_Retval = E_OK;
	*pu8_TicksNumber = OCR0;
	return u8_Retval;
}
E_STATUS_t TIMER0_SetCompareValue(uint8_t u8_TicksNumber)
{
	E_STATUS_t u8_Retval = E_OK;
	OCR0 = u8_TicksNumber;
	return u8_Retval;
}

E_STATUS_t TIMER0_GetCounterValue(ptr_uint8_t pu8_TicksNumber)
{
	E_STATUS_t u8_Retval = E_OK;
	*pu8_TicksNumber = TCNT0;
	return u8_Retval;
}
E_STATUS_t TIMER0_SetCounterValue(uint8_t u8_TicksNumber)
{
	E_STATUS_t u8_Retval = E_OK;
	TCNT0 = u8_TicksNumber;
	return u8_Retval;
}

E_STATUS_t TIMER0_GetOverflowValue(ptr_uint8_t pu8_TicksNumber)
{
	E_STATUS_t u8_Retval = E_OK;
	*pu8_TicksNumber = u8_TOVNumber;
	return u8_Retval;
}
E_STATUS_t TIMER0_SetOverflowValue(uint8_t u8_TicksNumber)
{
	E_STATUS_t u8_Retval = E_OK;
	u8_TOVNumber = u8_TicksNumber;
	return u8_Retval;
}

void TIMER0_CALLBACK_CompareMatch_INTERRUPT(PTR_VoidFuncVoid_t callback)
{
	CALLBACK_CM = callback;
}

void TIMER0_CALLBACK_Overflow_INTERRUPT(PTR_VoidFuncVoid_t callback)
{
	CALLBACK_OVF = callback;
}

ISR(TIMER0_COMP_vect)
{
	CALLBACK_CM();
}

ISR(TIMER0_OVF_vect)
{
	u8_TOVNumber++;
	CALLBACK_OVF();
}