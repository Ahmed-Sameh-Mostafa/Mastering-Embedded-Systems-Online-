/*
 * Stm32_F103C6_exti_driver.c
 *
 *  Created on: 8 Sep 2023
 *      Author: Lenovo
 */

#include "Stm32_F103C6_exti_driver.h"
#include "Stm32_F103C6_gpio_driver.h"


/*
 * ==================================================================================
 *										Generic Macros
 * ==================================================================================
 */
#define AFIO_GPIO_EXTI_Mapping(x)	(	(x == GPIOA) ? 0:\
										(x == GPIOB) ? 1:\
										(x == GPIOC) ? 2:\
										(x == GPIOD) ? 3:0 )




/*
 * ==================================================================================
 *										Generic Variables
 * ==================================================================================
 */

void (* GP_IRQ_CallBack[15])(void);


/*
 * ==================================================================================
 *										Generic Functions
 * ==================================================================================
 */

void Enable_NVIC(uint16_t IRQ)
{
	switch(IRQ)
	{
	case 0:
		NVIC_IRQ6_EXTI0_ENABLE();
		break;
	case 1:
		NVIC_IRQ7_EXTI1_ENABLE();
		break;
	case 2:
		NVIC_IRQ8_EXTI2_ENABLE();
		break;
	case 3:
		NVIC_IRQ9_EXTI3_ENABLE();
		break;
	case 4:
		NVIC_IRQ10_EXTI4_ENABLE();
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_ENABLE();
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_ENABLE();
		break;

	}
}

void Disable_NVIC(uint16_t IRQ)
{
	switch(IRQ)
	{
	case 0:
		NVIC_IRQ6_EXTI0_DISABLE();
		break;
	case 1:
		NVIC_IRQ7_EXTI1_DISABLE();
		break;
	case 2:
		NVIC_IRQ8_EXTI2_DISABLE();
		break;
	case 3:
		NVIC_IRQ9_EXTI3_DISABLE();
		break;
	case 4:
		NVIC_IRQ10_EXTI4_DISABLE();
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_DISABLE();
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_DISABLE();
		break;

	}
}


void Update_EXTI(EXTI_PinConfig_t* EXTI_Config)
{
	//1- Configure GPIO to be AF Input -> Floating input
	GPIO_PinConfig_t PinCfg;
	PinCfg.GPIO_PinNumber = EXTI_Config->EXTI_PIN.GPIO_PIN;
	PinCfg.GPIO_MODE = GPIO_MODE_AF_INPUT;
	MCAL_GPIO_Init(EXTI_Config->EXTI_PIN.GPIO_port, &PinCfg);
	//========================================================================

	//2- UPDATE AFIO to route between EXTI Line with PORT A,B,C,D

	uint8_t AFIO_EXTICR_Index 	 = EXTI_Config->EXTI_PIN.EXTI_InputLineNumber / 4;
	uint8_t AFIO_EXTICR_Position = (EXTI_Config->EXTI_PIN.EXTI_InputLineNumber % 4) * 4;

	//clear the four bits
	AFIO->EXTICR[AFIO_EXTICR_Index] &= ~(0xF << AFIO_EXTICR_Position);

	AFIO->EXTICR[AFIO_EXTICR_Index] |=  ((AFIO_GPIO_EXTI_Mapping(EXTI_Config->EXTI_PIN.GPIO_port) & 0xF) << AFIO_EXTICR_Position);
	//========================================================================

	//3- Update Rising or falling register
	EXTI->RTSR &= ~(1 << EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	EXTI->FTSR &= ~(1 << EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);

	if(EXTI_Config->Trigger_Case == EXTI_Trigger_RISING)
	{
		EXTI->RTSR |= (1 << EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	}
	else if(EXTI_Config->Trigger_Case == EXTI_Trigger_FALLING)
	{
		EXTI->FTSR |= (1 << EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	}
	else if(EXTI_Config->Trigger_Case == EXTI_Trigger_RISINGAndFALLING)
	{
		EXTI->RTSR |= (1 << EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
		EXTI->FTSR |= (1 << EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	}
	//========================================================================

	//4- Update IRQ Handling CALLBACK
	GP_IRQ_CallBack[EXTI_Config->EXTI_PIN.EXTI_InputLineNumber] = EXTI_Config->P_IRQ_CallBack;


	//========================================================================

	//5- Enable/ Disable IRQ EXTI & NVIC
	if(EXTI_Config->IRQ_EN == EXTI_IRQ_Enable)
	{
		EXTI->IMR	|= (1<<EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
		Enable_NVIC(EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	}
	else
	{
		EXTI->IMR	&= ~(1<<EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
		Enable_NVIC(EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	}

}






/*
 * ==================================================================================
 *									APIs Supported by "MCAL EXTI DRIVER"
 * ==================================================================================
 */


/**================================================================
 * @Fn				- MCAL_EXTI_DeInit
 * @brief			- reset EXTI Registers and NVIC corresponding IRQ MASK
 * @retval 			- None
 * Note				- None
 */

void MCAL_EXTI_GPIO_DeInit(void)
{
	EXTI->IMR 	= 	0x00000000;
	EXTI->EMR 	= 	0x00000000;
	EXTI->RTSR 	= 	0x00000000;
	EXTI->FTSR 	= 	0x00000000;
	EXTI->SWIER = 	0x00000000;

	//reseting by writing ones
	EXTI->PR 	= 	0xFFFFFFFF;

	//Disabling NVIC IRQ MASK
	NVIC_IRQ6_EXTI0_DISABLE();
	NVIC_IRQ7_EXTI1_DISABLE();
	NVIC_IRQ8_EXTI2_DISABLE();
	NVIC_IRQ9_EXTI3_DISABLE();
	NVIC_IRQ10_EXTI4_DISABLE();
	NVIC_IRQ23_EXTI5_9_DISABLE();
	NVIC_IRQ40_EXTI10_15_DISABLE();
}




/**================================================================
 * @Fn				- MCAL_EXTI_Init
 * @brief			- Initializes the EXTI according to the specified parameters in PinConfig
 * @param [in] 		- EXTI_Config set by @ref EXTI_define, EXTI_Trigger_define and EXTI_IRQ_define
 * @retval 			- None
 * Note				- Enable RCC clock for AFIO and corresponding GPIO
 */

void MCAL_EXTI_GPIO_Init(EXTI_PinConfig_t* EXTI_Config)
{
	Update_EXTI(EXTI_Config);
}




/**================================================================
 * @Fn				- MCAL_EXTI_Update
 * @brief			- Initializes the GPIOx PINy according to the specified parameters in PinConfig
 * @param [in] 		- GPIOx: where x can be (A..D depending on device used) to select GPIO peripheral
 * @param [in] 		- PinConfig pointer to a GPIO_PinConfig_t structure that contains
 * 					  the configuration information for the specified GPIO PIN.
 * @retval 			- None
 * Note				- None
 */

void MCAL_EXTI_GPIO_Update(EXTI_PinConfig_t* EXTI_Config)
{
	Update_EXTI(EXTI_Config);
}




/*
 * ==================================================================================
 * ==================================================================================
 *	=========================	  		ISR Functions		=========================
 * ==================================================================================
 * ==================================================================================
 */

void EXTI0_IRQHandler()
{
	EXTI->PR |= (1<<0);
	GP_IRQ_CallBack[0]();
}

void EXTI1_IRQHandler()
{
	EXTI->PR |= (1<<1);
	GP_IRQ_CallBack[1]();
}

void EXTI2_IRQHandler()
{
	EXTI->PR |= (1<<2);
	GP_IRQ_CallBack[2]();
}

void EXTI3_IRQHandler()
{
	EXTI->PR |= (1<<3);
	GP_IRQ_CallBack[3]();
}

void EXTI4_IRQHandler()
{
	EXTI->PR |= (1<<4);
	GP_IRQ_CallBack[4]();
}

void EXTI9_5_IRQHandler()
{
	if(EXTI->PR & (1<<5)) {EXTI->PR |= (1<<5);	GP_IRQ_CallBack[5]();}
	if(EXTI->PR & (1<<6)) {EXTI->PR |= (1<<6);	GP_IRQ_CallBack[6]();}
	if(EXTI->PR & (1<<7)) {EXTI->PR |= (1<<7);	GP_IRQ_CallBack[7]();}
	if(EXTI->PR & (1<<8)) {EXTI->PR |= (1<<8);	GP_IRQ_CallBack[8]();}
	if(EXTI->PR & (1<<9)) {EXTI->PR |= (1<<9);	GP_IRQ_CallBack[9]();}
}

void EXTI15_10_IRQHandler()
{
	if(EXTI->PR & (1<<10)) {EXTI->PR |= (1<<10);	GP_IRQ_CallBack[10]();}
	if(EXTI->PR & (1<<11)) {EXTI->PR |= (1<<11);	GP_IRQ_CallBack[11]();}
	if(EXTI->PR & (1<<12)) {EXTI->PR |= (1<<12);	GP_IRQ_CallBack[12]();}
	if(EXTI->PR & (1<<13)) {EXTI->PR |= (1<<13);	GP_IRQ_CallBack[13]();}
	if(EXTI->PR & (1<<14)) {EXTI->PR |= (1<<14);	GP_IRQ_CallBack[14]();}
	if(EXTI->PR & (1<<15)) {EXTI->PR |= (1<<15);	GP_IRQ_CallBack[15]();}
}
