/*
 * Lab_03.c
 *
 * Created: 23/08/2023 00:06:02
 * Author : Ahmed Sameh
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define SET_BIT(REGISTER, BIT)	REGISTER |= (1<<BIT)
#define CLEAR_BIT(REGISTER, BIT) REGISTER &= ~(1<<BIT)
#define TOGGLE_BIT(REGISTER, BIT) REGISTER ^= (1<<BIT)
#define READ_BIT(REGISTER, BIT) ((REGISTER & (1<<BIT)) >> BIT)

void GPIO_init(void)
{
	SET_BIT(DDRD, 5);
	SET_BIT(DDRD, 6);
	SET_BIT(DDRD, 7);
}

void EXTI_init(void)
{
	//interrupt 0 at any logical change
	SET_BIT(MCUCR, 0);
	CLEAR_BIT(MCUCR, 1);
	
	//interrupt 1 at rising edge
	SET_BIT(MCUCR, 2);
	SET_BIT(MCUCR, 3);
	
	//interrupt 2 at falling edge
	CLEAR_BIT(MCUCSR, 6);
	
	//enabling all external interrupts
	SET_BIT(GICR, 5);
	SET_BIT(GICR, 6);
	SET_BIT(GICR, 7);
}

int main(void)
{
	GPIO_init();
	EXTI_init();
	
	//enable global interrupt
	sei();
	
    while (1) 
    {
		//Turn off leds
		CLEAR_BIT(PORTD, 5);
		CLEAR_BIT(PORTD, 6);
		CLEAR_BIT(PORTD, 7);
    }
}

ISR(INT0_vect)
{
	SET_BIT(PORTD, 5);
	_delay_ms(1000);	
}

ISR(INT1_vect)
{
	SET_BIT(PORTD, 6);
	_delay_ms(1000);
}

ISR(INT2_vect)
{
	SET_BIT(PORTD, 7);
	_delay_ms(1000);
}

