/*
 * Stm32_F103C6_gpio_Driver.c
 *
 *  Created on: Aug 31, 2023
 *      Author: Lenovo
 */

//-------------------------------------------------
//Includes.
//-------------------------------------------------

#include "Stm32_F103C6_gpio_driver.h"

//*************************************************
static uint8_t Get_CRLH_Position(uint16_t PinNumber)
{
	switch (PinNumber)
	{
	case GPIO_PIN_0:
		return 0;
		break;

	case GPIO_PIN_1:
		return 4;
		break;

	case GPIO_PIN_2:
		return 8;
		break;

	case GPIO_PIN_3:
		return 12;
		break;

	case GPIO_PIN_4:
		return 16;
		break;

	case GPIO_PIN_5:
		return 20;
		break;

	case GPIO_PIN_6:
		return 24;
		break;

	case GPIO_PIN_7:
		return 28;
		break;

	case GPIO_PIN_8:
		return 0;
		break;

	case GPIO_PIN_9:
		return 4;
		break;

	case GPIO_PIN_10:
		return 8;
		break;

	case GPIO_PIN_11:
		return 12;
		break;

	case GPIO_PIN_12:
		return 16;
		break;

	case GPIO_PIN_13:
		return 20;
		break;

	case GPIO_PIN_14:
		return 24;
		break;

	case GPIO_PIN_15:
		return 28;
		break;

	default:
		break;
	}
	return 0;
}
//*************************************************


/**================================================================
 * @Fn				- MCAL_GPIO_Init
 * @brief			- Initializes the GPIOx PINy according to the specified parameters in PinConfig
 * @param [in] 		- GPIOx: where x can be (A..D depending on device used) to select GPIO peripheral
 * @param [in] 		- PinConfig pointer to a GPIO_PinConfig_t structure that contains
 * 					  the configuration information for the specified GPIO PIN.
 * @retval 			- None
 * Note				- Stm32F103C6 MCU has GPIO A, B, C, D Modules
 * 					  But LQFP48 Package has only GPIO A, B, PART of C/D exported as external PINs from the Module
 */
void MCAL_GPIO_Init (GPIO_TypeDef *GPIOx, GPIO_PinConfig_t* PinConfig)
{
	//this variable is used to store the address of CRL or CRH depending on the number of pin
	volatile uint32_t * config_register = NULL;

	//this variable hold the value of both CNF and MODE bits of the pin to be configured
	uint8_t pin_Config = 0;

	//in the next line config_register will either has address of CRL or CRH
	config_register = (PinConfig->GPIO_PinNumber > GPIO_PIN_7) ? &GPIOx->CRH: &GPIOx->CRL ;

	//clearing CNF and MODE bits in order to change them to the configuration we want later
	(*config_register) &= ~(0xF << Get_CRLH_Position(PinConfig->GPIO_PinNumber));

	if((PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_PP) || (PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_OD) || (PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_AF_PP) || (PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_AF_OD))
	{
		pin_Config = (((PinConfig->GPIO_MODE - 4) << 2) | PinConfig->GPIO_OUTPUT_Speed) & 0x0f;
	}
	else
	{
		if((PinConfig->GPIO_MODE == GPIO_MODE_Analog) || (PinConfig->GPIO_MODE == GPIO_MODE_INPUT_FLO))
		{
			pin_Config = ((PinConfig->GPIO_MODE << 2) | 0x0) & 0x0f;
		}
		else if(PinConfig->GPIO_MODE == GPIO_MODE_AF_INPUT)
		{
			pin_Config = ((GPIO_MODE_INPUT_FLO << 2) | 0x0) & 0x0f;
		}
		else
		{
			pin_Config = ((GPIO_MODE_INPUT_PD << 2) | 0x0) & 0x0f;
			if(PinConfig->GPIO_MODE == GPIO_MODE_INPUT_PU)
			{
				GPIOx->ODR |= PinConfig->GPIO_PinNumber;
			}
			else
			{
				GPIOx->ODR &= ~(PinConfig->GPIO_PinNumber);
			}
		}
	}

	(*config_register) |= ((pin_Config) << Get_CRLH_Position(PinConfig->GPIO_PinNumber) );
}


/**================================================================
 * @Fn				- MCAL_GPIO_DeInit
 * @brief			- Reset all the GPIO Registers
 * @param [in] 		- GPIOx: where x can be (A..D depending on device used) to select GPIO peripheral
 * @retval 			- None
 * Note				- None
 */
void MCAL_GPIO_DeInit (GPIO_TypeDef *GPIOx)
{
	if(GPIOx == GPIOA)
	{
		RCC->APB2RSTR |= (1<<2);
		RCC->APB2RSTR &= ~(1<<2);
	}
	else if(GPIOx == GPIOB)
	{
		RCC->APB2RSTR |= (1<<3);
		RCC->APB2RSTR &= ~(1<<3);
	}
	else if(GPIOx == GPIOC)
	{
		RCC->APB2RSTR |= (1<<4);
		RCC->APB2RSTR &= ~(1<<4);
	}
	else if(GPIOx == GPIOD)
	{
		RCC->APB2RSTR |= (1<<5);
		RCC->APB2RSTR &= ~(1<<5);
	}
}


/**================================================================
 * @Fn				- MCAL_GPIO_ReadPin
 * @brief			- Read Specific PIN
 * @param [in] 		- GPIOx: where x can be (A..D depending on device used) to select GPIO peripheral
 * @param [in] 		- PinNumber: Set Pin Number according to @ref GPIO_PINS_define
 * @retval 			- The input pin value (two values based on @ref GPIO_PIN_state)
 * Note				- None
 */
uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef * GPIOx, uint16_t PinNumber)
{
	uint8_t bitStatus;
	if(((GPIOx->IDR) & PinNumber) != (uint32_t )GPIO_PIN_RESET)
	{
		bitStatus = GPIO_PIN_SET;
	}
	else
	{
		bitStatus = GPIO_PIN_RESET;
	}
	return bitStatus;
}

/**================================================================
 * @Fn				- MCAL_GPIO_ReadPort
 * @brief			- Read Specific PORT
 * @param [in] 		- GPIOx: where x can be (A..D depending on device used) to select GPIO peripheral
 * @retval 			- The input port value
 * Note				- None
 */
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef * GPIOx)
{
	uint16_t portStatus;
	portStatus = (uint16_t)(GPIOx->IDR);
	return portStatus;
}



/**================================================================
 * @Fn				- MCAL_GPIO_WritePin
 * @brief			- Write on Specific pin
 * @param [in] 		- GPIOx: where x can be (A..D depending on device used) to select GPIO peripheral
 * @param [in] 		- PinNumber: specific the port bit to read @ref GPIO_PINS_define
 * @param [in] 		- Value: Pin value
 * @retval 			- None
 * Note				- None
 */
void MCAL_GPIO_WritePin(GPIO_TypeDef * GPIOx, uint16_t PinNumber,uint8_t value)
{
	if(value != GPIO_PIN_RESET)
	{
		GPIOx->BSRR = (uint32_t)PinNumber;
	}
	else
	{
		GPIOx->BRR = (uint32_t)PinNumber;
	}
}


/**================================================================
 * @Fn				- MCAL_GPIO_WritePort
 * @brief			- Write on Specific PORT
 * @param [in] 		- GPIOx: where x can be (A..D depending on device used) to select GPIO peripheral
 * @param [in] 		- Value: Port value
 * @retval 			- None
 * Note				- None
 */
void MCAL_GPIO_WritePort(GPIO_TypeDef * GPIOx, uint16_t value)
{
	GPIOx->ODR = (uint32_t)value;
}


/**================================================================
 * @Fn				- MCAL_GPIO_TogglePin
 * @brief			- Toggle Specific pin
 * @param [in] 		- GPIOx: where x can be (A..D depending on device used) to select GPIO peripheral
 * @param [in] 		- PinNumber: specific the port bit to read @ref GPIO_PINS_define
 * @retval 			- None
 * Note				- None
 */
void MCAL_GPIO_TogglePin(GPIO_TypeDef * GPIOx, uint16_t PinNumber)
{
	GPIOx->ODR ^= (PinNumber);
}



/**================================================================
 * @Fn				- MCAL_GPIO_LockPin
 * @brief			- The locking mechanism allows the IO configuration to be frozen
 * @param [in] 		- GPIOx: where x can be (A..D depending on device used) to select GPIO peripheral
 * @param [in] 		- PinNumber: specific the port bit to read @ref GPIO_RETURN_LOCK
 * @retval 			- OK if pin configure is locked Or ERROR if pin is not locked (OK & ERROR are defined @ref GPIO_RETURN_LOCK)
 * Note				- None
 */
uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef * GPIOx, uint16_t PinNumber)
{
	volatile uint32_t tmp = (1<<16);
	tmp |= PinNumber;

	//write 1
	GPIOx->LCKR = tmp;
	//write 0
	GPIOx->LCKR = PinNumber;
	//write 1
	GPIOx->LCKR = tmp;
	//read 0
	tmp = GPIOx->LCKR;
	// read 1 optional
	if((uint32_t)(GPIOx->LCKR & (1<< 16)))
	{
		return GPIO_RETURN_LOCK_ENABLED;
	}
	else
	{
		return GPIO_RETURN_LOCK_ERROR;
	}
}
