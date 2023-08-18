


typedef volatile unsigned int vuint32_t;
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


// register address
#define GPIOA_BASE 0x40010800
#define GPIOA_CRH *(vuint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_ODR *(vuint32_t *)(GPIOA_BASE + 0x0c)

// clock address
#define RCC_BASE 0x40021000
#define RCC_APB2ENR *(vuint32_t *)(RCC_BASE + 0x18)


int main(void)
{
	// Enable clock
	RCC_APB2ENR |= 1 << 2;
	//Init GPIOA
	GPIOA_CRH &= 0xFF0FFFFF;
	GPIOA_CRH |= 0x00200000;

	while(1)
	{
		GPIOA_ODR |= 1 << 13;
		for(int i = 0; i < 5000; i++);
		GPIOA_ODR &= ~(1 << 13);
		for(int i = 0; i < 5000; i++);
	}
}
