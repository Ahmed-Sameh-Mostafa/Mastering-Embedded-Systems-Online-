/*
 * Stm32_F103C6_gpio_Driver.h
 *
 *  Created on: Aug 31, 2023
 *      Author: Lenovo
 */

#ifndef INC_STM32_F103C6_GPIO_DRIVER_H_
#define INC_STM32_F103C6_GPIO_DRIVER_H_

//-------------------------------------------------
//Includes.
//-------------------------------------------------

#include "STM32_F103C6.h"

//*************************************************
//*************************************************

//config structure
typedef struct
{
	uint16_t GPIO_PinNumber; 		// specifies the GPIO pin to be configured
									// this parameter can be a value of @ref GPIO_PINS_define

	uint8_t	 GPIO_MODE;				// specifies Operating Mode for the selected Pins
									// this parameter can be a value of @ref GPIO_MODE_define
	uint8_t	 GPIO_OUTPUT_Speed;		// specifies the speed for the selected pins
									// this parameter can be a value of @ref GPIO_SPEED_define
}GPIO_PinConfig_t;


// @ref GPIO_PIN_state
#define GPIO_PIN_SET					1
#define GPIO_PIN_RESET					0

// @ref GPIO_RETURN_LOCK
#define GPIO_RETURN_LOCK_ENABLED		1
#define GPIO_RETURN_LOCK_ERROR			0

//=================================================
// Macros Configuration References
//=================================================

// @ref GPIO_PINS_define
#define GPIO_PIN_0						((uint16_t)0x0001) //PIN 0 Selected ~ 0000 0000 0000 0001
#define GPIO_PIN_1						((uint16_t)0x0002) //PIN 0 Selected ~ 0000 0000 0000 0010
#define GPIO_PIN_2						((uint16_t)0x0004) //PIN 0 Selected ~ 0000 0000 0000 0100
#define GPIO_PIN_3						((uint16_t)0x0008) //PIN 0 Selected ~ 0000 0000 0000 1000
#define GPIO_PIN_4						((uint16_t)0x0010) //PIN 0 Selected ~ 0000 0000 0001 0000
#define GPIO_PIN_5						((uint16_t)0x0020) //PIN 0 Selected ~ 0000 0000 0010 0000
#define GPIO_PIN_6						((uint16_t)0x0040) //PIN 0 Selected ~ 0000 0000 0100 0000
#define GPIO_PIN_7						((uint16_t)0x0080) //PIN 0 Selected ~ 0000 0000 1000 0000
#define GPIO_PIN_8						((uint16_t)0x0100) //PIN 0 Selected ~ 0000 0001 0000 0000
#define GPIO_PIN_9						((uint16_t)0x0200) //PIN 0 Selected ~ 0000 0010 0000 0000
#define GPIO_PIN_10						((uint16_t)0x0400) //PIN 0 Selected ~ 0000 0100 0000 0000
#define GPIO_PIN_11						((uint16_t)0x0800) //PIN 0 Selected ~ 0000 1000 0000 0000
#define GPIO_PIN_12						((uint16_t)0x1000) //PIN 0 Selected ~ 0001 0000 0000 0000
#define GPIO_PIN_13						((uint16_t)0x2000) //PIN 0 Selected ~ 0010 0000 0000 0000
#define GPIO_PIN_14						((uint16_t)0x4000) //PIN 0 Selected ~ 0100 0000 0000 0000
#define GPIO_PIN_15						((uint16_t)0x8000) //PIN 0 Selected ~ 1000 0000 0000 0000
#define GPIO_PIN_ALL					((uint16_t)0xFFFF) //PIN 0 Selected ~ 1111 1111 1111 1111

#define GPIO_PIN_MASK					0x0000FFFFu		   //PIN Mask for assert test


// @ref GPIO_MODE_define
//0: Analog mode
//1: Floating input (reset state)
//2: Input with pull-up
//3: Input with pull-down
//4: output push-pull
//5: output Open-drain
//6: Alternate function output Push-pull
//7: Alternate function output Open-drain
//8: Alternate function Input

#define GPIO_MODE_Analog				0x00000000u // Analog mode
#define GPIO_MODE_INPUT_FLO				0x00000001u // Input floating mode
#define GPIO_MODE_INPUT_PU				0x00000002u // Input pull up mode
#define GPIO_MODE_INPUT_PD				0x00000003u // Input pull down mode
#define GPIO_MODE_OUTPUT_PP				0x00000004u // Output push pull mode
#define GPIO_MODE_OUTPUT_OD				0x00000005u // Output open drain mode
#define GPIO_MODE_OUTPUT_AF_PP			0x00000006u // Alternate function push pull mode
#define GPIO_MODE_OUTPUT_AF_OD			0x00000007u // Alternate function open drain
#define GPIO_MODE_AF_INPUT				0x00000008u // Alternate function input


// @ref GPIO_SPEED_define
//00: Input mode (reset state)
//01: Output mode, max speed 10 MHz.
//10: Output mode, max speed 2 MHz.
//11: Output mode, max speed 50 MHz.

#define GPIO_SPEED_10M					0x00000001u //output mode, max speed at 10 MHz.
#define GPIO_SPEED_2M					0x00000002u //output mode, max speed at  2 MHz.
#define GPIO_SPEED_50M					0x00000003u //output mode, max speed at 50 MHz.


/*
 * ==================================================================================
 *									APIs Supported by "MCAL GPIO DRIVER"
 * ==================================================================================
 */

void MCAL_GPIO_Init (GPIO_TypeDef *GPIOx, GPIO_PinConfig_t* PinConfig);
void MCAL_GPIO_DeInit (GPIO_TypeDef *GPIOx);

uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef * GPIOx, uint16_t PinNumber);
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef * GPIOx);

void MCAL_GPIO_WritePin(GPIO_TypeDef * GPIOx, uint16_t PinNumber,uint8_t value);
void MCAL_GPIO_WritePort(GPIO_TypeDef * GPIOx, uint16_t value);

void MCAL_GPIO_TogglePin(GPIO_TypeDef * GPIOx, uint16_t PinNumber);

uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef * GPIOx, uint16_t PinNumber);

// adder for smart car parking
void MCAL_GPIO_WriteGroup(GPIO_TypeDef * GPIOx,uint16_t Value,uint16_t mask);


#endif /* INC_STM32_F103C6_GPIO_DRIVER_H_ */
