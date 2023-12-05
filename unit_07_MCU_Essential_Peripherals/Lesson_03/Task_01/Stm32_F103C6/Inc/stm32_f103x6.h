/*
 * Stm32_F103C6.h
 *
 *  Created on: Aug 31, 2023
 *      Author: Lenovo
 */

#ifndef INC_STM32_F103X6_H_
#define INC_STM32_F103X6_H_


//-------------------------------------------------
//Includes.
//-------------------------------------------------

#include "stdlib.h"
#include "stdint.h"
//*************************************************
//*************************************************

//-------------------------------------------------
//Base Addresses for memories
//-------------------------------------------------

#define Flash_Memory_BASE 						0x08000000UL
#define System_Memory_BASE 						0x1FFFF000UL
#define SRAM_Memory_BASE 						0x20000000UL

#define Peripherals_Memory_BASE					0x40000000UL

#define Cortex_M3_Internal_Peripherals_BASE		0xE0000000UL
//*************************************************
//*************************************************

//-------------------------------------------------
//Base Addresses for AHB peripherals
//-------------------------------------------------

#define RCC_BASE								0x40021000UL
//*************************************************
//*************************************************

//-------------------------------------------------
//Base Addresses for APB2 peripherals
//-------------------------------------------------

//		GPIO
// 			A, B fully included inside LQFP48 package
#define GPIOA_BASE								0x40010800UL
#define GPIOB_BASE								0x40010C00UL

// 			C, D fully included inside LQFP48 package
#define GPIOC_BASE								0x40011000UL
#define GPIOD_BASE								0x40011400UL

// 			E, F, G not included inside LQFP48 package


//		EXTI
#define EXTI_BASE								0x40010400UL

//		AFIO
#define AFIO_BASE								0x40010000UL
//*************************************************
//*************************************************

//-------------------------------------------------
//Base Addresses for APB1 peripherals
//-------------------------------------------------

//*************************************************
//*************************************************

//========================================================================================

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//Peripherals registers
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//		Peripheral Registers: RCC
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
}RCC_TypeDef;

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//		Peripheral Registers: GPIO
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
}GPIO_TypeDef;

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//		Peripheral Registers: EXTI
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_TypeDef;

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//		Peripheral Registers: AFTI
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR1;
	volatile uint32_t EXTICR2;
	volatile uint32_t EXTICR3;
	volatile uint32_t EXTICR4;
			 uint32_t RESERVED0;
	volatile uint32_t MAPR2;
}AFIO_TypeDef;
//========================================================================================


//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//		Peripheral Instants:
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

#define RCC						((RCC_TypeDef *)  RCC_BASE)

#define GPIOA					((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB					((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC					((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD					((GPIO_TypeDef *) GPIOD_BASE)

#define EXTI					((EXTI_TypeDef *) EXTI_BASE)

#define AFIO					((AFIO_TypeDef *) AFIO_BASE)
//========================================================================================


//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//		Clock enable macros
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

#define RCC_GPIOA_CLK_EN()		(RCC->APB2ENR |= 1<<2)
#define RCC_GPIOB_CLK_EN()		(RCC->APB2ENR |= 1<<3)
#define RCC_GPIOC_CLK_EN()		(RCC->APB2ENR |= 1<<4)
#define RCC_GPIOD_CLK_EN()		(RCC->APB2ENR |= 1<<5)

#define RCC_AFIO_CLK_EN()		(RCC->APB2ENR |= 1<<0)
//========================================================================================
#endif /* INC_STM32_F103X6_H_ */
