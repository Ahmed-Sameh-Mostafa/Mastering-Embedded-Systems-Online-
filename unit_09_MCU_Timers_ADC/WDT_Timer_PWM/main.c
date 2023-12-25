 /*
 * Task_02.c
 *
 * Created: 21/12/2023 00:42:11
 * Author : Lenovo
 */ 
#define F_CPU 8000000UL
#include "AvrMemoryMap.h"
#include "Timer_PWM.h"
#include "WDT.h"
#include "Utils.h"
#include<util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>


#define WDT_Test		0
#define Timer_Test		1
#define PWM_Test		2

#define Test_In_Main	PWM_Test

#if (Test_In_Main == WDT_Test)
void WDT_Test_code();
#elif(Test_In_Main == Timer_Test)
void Timer_Test_code();
#elif(Test_In_Main == PWM_Test)
void PWM_Test_code();
#endif

int main(void)
{
	
	#if (Test_In_Main == WDT_Test)
	WDT_Test_code();
	#elif(Test_In_Main == Timer_Test)
	Timer_Test_code();
	#elif(Test_In_Main == PWM_Test)
	PWM_Test_code();
	#endif
	
   
	return 0;
}


#if (Test_In_Main == WDT_Test)
void WDT_Test_code()
{
	#define LED_DDR		DDRC
	#define LED_PORT	PORTC
	#define LED_PIN		0
	
	SET_BIT(LED_DDR,0);
	CLEAR_BIT(LED_PORT,0);
	_delay_ms(500);
	while (1)
	{
		WDT_ON();
		TOGGLE_BIT(LED_PORT, 0);
		_delay_ms(2000);
		WDT_OFF();
	}
}
#elif(Test_In_Main == Timer_Test)
extern uint8_t u8_TOVNumber;
void TOIE_Callback()
{
	PORTA = ~PORTA;
}
void Timer_Test_code()
{
	
	DDRA = 0xFF;
	sei();
	TIMER0_CALLBACK_CompareMatch_INTERRUPT(TOIE_Callback);
	STIMER0_CONFIG config = {CTC, OCIE_ENABLE, TOIE_DISABLE, NO_};
	TIMER0_SetCompareValue(0xF0);
	TIMER0_Init(&config);
	
	
	while (1)
	{
	}
	

}
#elif(Test_In_Main == PWM_Test)
void PWM_Test_code()
{
	unsigned char counter = 0x00;
	//setting OC0 pin to output mode
	SET_BIT(DDRB,3);
	TIMER0_SetCounterValue(0x00);
	STIMER0_CONFIG config = {PWM_FAST_NonInverting, OCIE_DISABLE, TOIE_DISABLE, PRESCALING_CLK64};
	TIMER0_SetCompareValue(counter);
	TIMER0_Init(&config);
	while (1)
	{
		TIMER0_SetCompareValue(counter);
		_delay_ms(350);
		counter += 15;
	}
}
#endif