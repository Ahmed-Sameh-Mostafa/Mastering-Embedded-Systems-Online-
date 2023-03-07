// created by Ahmed Sameh in Mastering embedded systems diploma
#ifndef MAIN_H
#define MAIN_H
#include <platform_Types.h>

//register address 
#define RCC_BASE	0x40021000
#define GPIOA_BASE	0X40010800
#define RCC_APB2ENR	*(volatile uint32 *)(RCC_BASE 	+ 0x18)
#define GPIOA_CRH	*(volatile uint32 *)(GPIOA_BASE 	+ 0x04)
#define GPIOA_ODR	*(volatile uint32 *)(GPIOA_BASE	+ 0X0C)

//bit fields
#define RCC_IOPAEN	(1<<2)
#define GPIOA13		(1UL<<13)

typedef union {
	vuint32_t all_fields;
	struct{
		vuint32_t	reserved:13;
		vuint32_t P_13:1;
	} Pin;
} R_ODR_t;
#endif