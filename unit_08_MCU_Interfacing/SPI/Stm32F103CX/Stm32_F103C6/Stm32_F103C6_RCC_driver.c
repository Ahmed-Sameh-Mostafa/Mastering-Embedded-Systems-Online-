/*
 * Stm32_F103C6_RCC_driver.c
 *
 *  Created on: 8 Sep 2023
 *      Author: Lenovo
 */

#include "Stm32_F103C6_RCC_driver.h"
#include "Stm32_F103C6_gpio_driver.h"


const uint8_t APBPrescTable[8U] = {0, 0, 0, 0, 1, 2, 3, 4};
const uint8_t AHBPrescTable[16U] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

uint32_t MCAL_RCC_GetSYS_CLKFreq(void)
{
	switch( (RCC->CFGR >> 2) & 0b11)
	{
	case 0:
		return HSI_RC_CLK;
		break;
	case 1:
		return HSE_Clock;
		break;
	case 2:
		return 16000000;
		break;
	}
}

uint32_t MCAL_RCC_GetHCLKFreq(void)
{
	return (MCAL_RCC_GetSYS_CLKFreq() >> AHBPrescTable[((RCC->CFGR >> 4) & 0xF)]);
}

uint32_t MCAL_RCC_GetPCLK1Freq(void)
{
	return (MCAL_RCC_GetHCLKFreq() >> APBPrescTable[((RCC->CFGR >> 8) & 0b111)]);
}

uint32_t MCAL_RCC_GetPCLK2Freq(void)
{
	return (MCAL_RCC_GetHCLKFreq() >> APBPrescTable[((RCC->CFGR >> 11) & 0b111)]);
}
