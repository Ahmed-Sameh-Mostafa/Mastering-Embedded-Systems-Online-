/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "stm32_f103x6.h"
#include "Stm32_F103C6_gpio_driver.h"
#include "lcd.h"
#include "keypad.h"


void clock_init()
{
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();
}

void GPIO_init()
{
	GPIO_PinConfig_t PinCfg;

	//PB9 input floating
	PinCfg.GPIO_PinNumber = GPIO_PIN_9;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &PinCfg);

	//PB10 output push pull
	PinCfg.GPIO_PinNumber = GPIO_PIN_10;
//	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
//	PinCfg.GPIO_OUTPUT_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &PinCfg);

	//PB11
	PinCfg.GPIO_PinNumber = GPIO_PIN_11;
	MCAL_GPIO_Init(GPIOB, &PinCfg);

	//PB12
	PinCfg.GPIO_PinNumber = GPIO_PIN_12;
	MCAL_GPIO_Init(GPIOB, &PinCfg);

	//PB13
	PinCfg.GPIO_PinNumber = GPIO_PIN_13;
	MCAL_GPIO_Init(GPIOB, &PinCfg);

	//PB14
	PinCfg.GPIO_PinNumber = GPIO_PIN_14;
	MCAL_GPIO_Init(GPIOB, &PinCfg);

	//PB15
	PinCfg.GPIO_PinNumber = GPIO_PIN_15;
	MCAL_GPIO_Init(GPIOB, &PinCfg);
}

void wait_ms_main(uint32_t time)
{
	uint32_t i,j;
	for(i = 0; i < time; i++)
		for(j = 0; j < 255; j++);
}

// 7 segment
#define ZERO 0x40
#define ONE 0x79
#define TWO 0x24
#define THREE 0x30
#define FOUR 0x19
#define FIVE 0x12
#define SIX 0x02
#define SEVEN 0x78
#define EIGHT 0x00
#define NINE 0x10

int main(void)
{
	uint8_t key_pressed;
	uint8_t seg[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, ZERO};
	uint8_t lcd[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
    clock_init();
    GPIO_init();
    LCD_INIT();

    LCD_WRITE_STRING("Hey there");
    wait_ms_main(500);
    LCD_clear_screen();

    for(uint8_t i = 0; i < 11; i++)
    {
    	MCAL_GPIO_WritePort(GPIOB, seg[i]<<9);
    	LCD_WRITE_CHAR(lcd[i]);
    	wait_ms_main(100);
    }
    Keypad_init();
    LCD_clear_screen();
    LCD_WRITE_STRING("Keypad is ready");
    wait_ms_main(500);
	LCD_clear_screen();
    while(1)
    {
    	key_pressed = Keypad_getkey();
		switch(key_pressed){
			case 'A':
			break;
			case '?':
			LCD_clear_screen();
			break;
			default:
			LCD_WRITE_CHAR(key_pressed);
			break;
		}
    }
}
