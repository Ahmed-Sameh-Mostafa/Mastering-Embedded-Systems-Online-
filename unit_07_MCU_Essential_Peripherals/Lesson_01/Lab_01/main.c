/*
 * 	Author: Ahmed Sameh
 *
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
#define GPIOA_IDR 	*(vuint32_t *)(GPIOA_BASE + 0x08)
#define GPIOA_ODR 	*(vuint32_t *)(GPIOA_BASE + 0x0c)

// GPIO address
#define GPIOB_BASE 	0x40010C00
#define GPIOB_CRL 	*(vuint32_t *)(GPIOB_BASE + 0x00)
#define GPIOB_CRH 	*(vuint32_t *)(GPIOB_BASE + 0x04)
#define GPIOB_IDR 	*(vuint32_t *)(GPIOB_BASE + 0x08)
#define GPIOB_ODR 	*(vuint32_t *)(GPIOB_BASE + 0x0c)



void clock_init(void)
{
	RCC_CFGR |= (0b100 << 8);

	RCC_CFGR |= (0b101 << 11);

	// Enable clock for gpio a
	RCC_APB2ENR |= 1 << 2;

	// Enable clock for gpio b
	RCC_APB2ENR |= 1 << 3;
}

void gpio_init(void)
{
	//	GPIO A
	GPIOA_CRH = 0;
	GPIOA_CRL = 0;
	GPIOA_ODR = 0;

	//pin A1: 	floating input, MODE bits already are in reset from the previous lines
	GPIOA_CRL |= 0b01 << 6;

	//pin A13: 	floating input, MODE bits already are in reset from the previous lines
	GPIOA_CRH |= 0b01 << 22;
	/***************************************************/
	// GPIO B

	GPIOB_CRH = 0;
	GPIOB_CRL = 0;
	GPIOB_ODR = 0;


	//pin 	B1: 	output push-pull, mode = 01 (crl already done)
	GPIOB_CRL |= 0b01 << 4;

	//pin 	B13: 	output push-pull, mode = 01 (crh already done)
	GPIOB_CRH |= 0b01 << 20;
}

void wait_ms(uint32_t time)
{
	uint32_t i, j;
	for(i = 0; i < time; i++)
		for(j = 0; j < 255; j++);
}


int main(void)
{
	//initialize clocks
	clock_init();
	//initialize gpio
	gpio_init();


	while(1)
	{
		if(((GPIOA_IDR & (1<<1)) >> 1) == 0)
		{
			GPIOB_ODR ^= 1<<1;
			while(((GPIOA_IDR & 1<<1) >> 1) == 0);
		}
		if(((GPIOA_IDR & (1<<13)) >> 13) == 1)
		{
			GPIOB_ODR ^= 1<<13;
		}
		wait_ms(1);
	}
}
