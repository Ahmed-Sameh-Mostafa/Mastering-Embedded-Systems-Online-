/*
 * 	Author: Ahmed Sameh
 * 	Description:
 */


typedef volatile unsigned int vuint32_t;
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

// clock address
#define RCC_BASE 	0x40021000
#define RCC_CFGR	*(vuint32_t *)(RCC_BASE + 0x04)
#define RCC_APB2ENR *(vuint32_t *)(RCC_BASE + 0x18)

// GPIO address
#define GPIOA_BASE 	0x40010800
#define GPIOA_CRL 	*(vuint32_t *)(GPIOA_BASE + 0x00)
#define GPIOA_CRH 	*(vuint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_ODR 	*(vuint32_t *)(GPIOA_BASE + 0x0c)

//EXTI address
#define EXTI_BASE 	0x40010400
#define EXTI_IMR 	*(vuint32_t *)(EXTI_BASE + 0x00)
#define EXTI_RTSR 	*(vuint32_t *)(EXTI_BASE + 0x08)
#define EXTI_PR		*(vuint32_t *)(EXTI_BASE + 0x14)

// AFIO address
#define AFIO_BASE 0x40010000
#define AFIO_EXTICR1 *(vuint32_t *)(AFIO_BASE + 0x08)

// NVIC address
#define NVIC_ISER *(vuint32_t *)(0xE000E100)



void clock_init(void)
{
	RCC_CFGR |= (0b100 << 8);

	RCC_CFGR |= (0b101 << 11);
}

void gpio_a_init(void)
{
	// Enable clock for gpio
	RCC_APB2ENR |= 1 << 2;

	// Enable clock for AFIO
	RCC_APB2ENR |= 1 << 0;

	//Init GPIOA: pin 13 output
	GPIOA_CRH &= 0xFF0FFFFF;
	GPIOA_CRH |= 0x00200000;

	//floating input for pin 0
	GPIOA_CRL |= (1<<2);

	//Init pin 0 for external interrupt
	AFIO_EXTICR1 = (AFIO_EXTICR1 & (~(0x000F))) | (0b0000);
}

void exti_init(void)
{
	EXTI_IMR |= (1<<0);
	EXTI_RTSR |= (1<<0);
	NVIC_ISER |= (1<<6);
}

void EXTI0_IRQHandler()
{
    GPIOA_ODR ^= (1<<13) ;

    EXTI_PR |= (1<<0);
}

int main(void)
{
	//initialize clocks
	clock_init();
	//initialize gpio
	gpio_a_init();
	//initialize exti
	exti_init();

	while(1);
}
