/*
 * Keypad.h
 *
 *  Created on: Oct 28, 2021
 *      Author: Mostafa Mahmoud Elshiekh
 */

#include "STM32_F103C6.h"
#include "Stm32_F103C6_gpio_driver.h"

#ifndef KEYPAD_KEYPAD_H_
#define KEYPAD_KEYPAD_H_

#define KEYPAD_PORT GPIOB

#define Keypad_rows_no	4			// Rows will be used as input
#define Keypad_cols_no	3			// Cols will be used as ouput

#define Keypad_rows {				\
						GPIO_PIN_0, \
						GPIO_PIN_1,	\
						GPIO_PIN_3,	\
						GPIO_PIN_4,	\
					}

#define Keypad_cols	{				\
						GPIO_PIN_5,	\
						GPIO_PIN_6, \
						GPIO_PIN_7	\
					}

#define Keypad_keys {						\
						{'*', '0', '#'},	\
						{'7', '8', '9'},	\
						{'4', '5', '6'},	\
						{'1', '2', '3'},	\
					}


void keypad_Init();
uint8_t keypad_Read(void);

#endif /* KEYPAD_KEYPAD_H_ */
