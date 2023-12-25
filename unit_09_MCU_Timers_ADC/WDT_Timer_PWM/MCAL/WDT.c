/*
 * WDT.c
 *
 * Created: 24/12/2023 13:15:04
 *  Author: Lenovo
 */ 
#include "WDT.h"


void WDT_ON()
{
	WDTCR |= (1 << WDP1) | (1 << WDP2) | (1 << WDE);
	CLEAR_BIT(WDTCR,WDP0);
}

void WDT_OFF()
{
	WDTCR = (1<<WDTOE)|(1<<WDE);
	WDTCR = 0x00;
}