/*
 * Stm32_F103C6_USART_driver.c
 *
 *  Created on: 8 Sep 2023
 *      Author: Lenovo
 */

#include "Stm32_F103C6_USART_driver.h"
#include "Stm32_F103C6_gpio_driver.h"


/*
 * ==================================================================================
 *										Generic Variables
 * ==================================================================================
 */

UART_Config Global_UART_Config[3];



/*
 * ==================================================================================
 *										Generic Functions
 * ==================================================================================
 */





/*
 * ==================================================================================
 *									APIs Supported by "MCAL EXTI DRIVER"
 * ==================================================================================
 */


/**================================================================
 * @Fn				- MCAL_UART_Init
 * @brief			- Initializes UART (Supported feature ASYNCH. Only)
 * @param [in]		- USARTX: where x can be (1..3 depending on device used)
 * @param [in]		- UART_Config: All Uart configuration
 * @retval 			- None
 * Note				- support for now ASynch mode & clock 8 Mhz
 */
void MCAL_UART_Init(USART_TypeDef* USARTx, UART_Config* UART_Config)
{
	uint32_t pclk, BRR;

	// enable the clock for given usart peripheral
	if(USARTx == USART1)
	{
		RCC_USART1_CLOCK_EN();
		Global_UART_Config[0] = *UART_Config;
	}
	else if(USARTx == USART2)
	{
		RCC_USART2_CLOCK_EN();
		Global_UART_Config[1] = *UART_Config;
	}
	else if(USARTx == USART3)
	{
		RCC_USART3_CLOCK_EN();
		Global_UART_Config[2] = *UART_Config;
	}


	// Enable Usart module
	USARTx->CR1 |= (1<<13);

	// Enable uart tx and rx
	USARTx->CR1 |= UART_Config->USART_Mode;

	//Payload width
	USARTx->CR1 |= UART_Config->Payload_Length;

	//Parity bits
	USARTx->CR1 |= UART_Config->Parity;

	// stop bits
	USARTx->CR2 |= UART_Config->StopBits;

	//flow control
	USARTx->CR3 |= UART_Config->HwFlowCtl;

	//Baud Rate

	if(USARTx == USART1)
		pclk = MCAL_RCC_GetPCLK2Freq();
	else
		pclk = MCAL_RCC_GetPCLK1Freq();

	BRR = UART_BRR_Register(pclk, UART_Config->BaudRate);
	USARTx->BRR = BRR;

	// enable / disable interrupt
	if(UART_Config->IRQ_Enable != UART_IRQ_Enable_NONE)
	{
		USARTx->CR1 |= UART_Config->IRQ_Enable;

		//ENABLE NVIC for usartx irq
		if(USARTx == USART1)
			NVIC_IRQ37_USART1_ENABLE();
		else if(USARTx == USART2)
			NVIC_IRQ38_USART2_ENABLE();
		else if(USARTx == USART3)
			NVIC_IRQ39_USART3_ENABLE();

	}

}


/**================================================================
 * @Fn				- MCAL_UART_DeInit
 * @brief			- deinitializes uart
 * @param [in]		- USARTX: where x can be (1..3 depending on device used)
 * @retval 			- None
 * Note				- None
 */
void MCAL_UART_DeInit(USART_TypeDef* USARTx)
{
	if(USARTx == USART1)
		{
			RCC_USART1_RESET();
			NVIC_IRQ37_USART1_DISABLE();
		}
	else if(USARTx == USART2)
		{
			RCC_USART2_RESET();
			NVIC_IRQ38_USART2_DISABLE();
		}
	else if(USARTx == USART3)
		{
			RCC_USART3_RESET();
			NVIC_IRQ39_USART3_DISABLE();
		}
}



/**================================================================
 * @Fn				- MCAL_UART_GPIO_Set_Pins
 * @brief			- initialize GPIO pins
 * @param[in]		- USARTx: where x can be(1..3 depending on device)
 * @retval 			- None
 * Note				- Should enable the corresponding ALT & GPIO in RCC clock Also called after MCAL_UART_Init()
 */
void MCAL_UART_GPIO_Set_Pins(USART_TypeDef* USARTx)
{
	GPIO_PinConfig_t PinCfg;

	if(USARTx == USART1)
	{
		//PA9 TX		PA10 RX			PA11 CTS 			PA12 RTS

		//PA9 TX
		PinCfg.GPIO_PinNumber = GPIO_PIN_9;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		PinCfg.GPIO_OUTPUT_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		//PA10 RX
		PinCfg.GPIO_PinNumber = GPIO_PIN_10;
		PinCfg.GPIO_MODE = GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		if(Global_UART_Config[0].HwFlowCtl == UART_HwFlowCtl_CTS || Global_UART_Config[0].HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
		{
			//PA11 CTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_11;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}

		if(Global_UART_Config[0].HwFlowCtl == UART_HwFlowCtl_RTS || Global_UART_Config[0].HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
		{
			//PA12 RTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_12;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_OUTPUT_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}
	}
	else if(USARTx == USART2)
	{
		//PA2 TX		PA3 RX			PA0 CTS 			PA1 RTS

		//PA2 TX
		PinCfg.GPIO_PinNumber = GPIO_PIN_2;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		PinCfg.GPIO_OUTPUT_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		//PA3 RX
		PinCfg.GPIO_PinNumber = GPIO_PIN_3;
		PinCfg.GPIO_MODE = GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		if(Global_UART_Config[1].HwFlowCtl == UART_HwFlowCtl_CTS || Global_UART_Config[1].HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
		{
			//PA0 CTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_0;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}

		if(Global_UART_Config[1].HwFlowCtl == UART_HwFlowCtl_RTS || Global_UART_Config[1].HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
		{
			//PA1 RTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_1;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_OUTPUT_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}
	}

	else if(USARTx == USART3)
	{
		//PB10 TX		PB11 RX			PB13 CTS 			PB14 RTS

		//PB10 TX
		PinCfg.GPIO_PinNumber = GPIO_PIN_10;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		PinCfg.GPIO_OUTPUT_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &PinCfg);

		//PB11 RX
		PinCfg.GPIO_PinNumber = GPIO_PIN_11;
		PinCfg.GPIO_MODE = GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIOB, &PinCfg);

		if(Global_UART_Config[2].HwFlowCtl == UART_HwFlowCtl_CTS || Global_UART_Config[2].HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
		{
			//PB13 CTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_13;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &PinCfg);
		}

		if(Global_UART_Config[2].HwFlowCtl == UART_HwFlowCtl_RTS || Global_UART_Config[2].HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
		{
			//PB14 RTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_14;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_OUTPUT_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &PinCfg);
		}
	}
}



/**================================================================
 * @Fn				- MCAL_UART_SendData
 * @brief			- send buffer on uart
 * @param [in]		- USARTX: where x can be (1..3 depending on device used)
 * @param [in]		- pTxBuffer Buffer
 * @param [in]		- Polling_mechism PollingEn: Enable pooling or disable it
 * @retval 			- None
 * Note				- None
 */
void MCAL_UART_SendData(USART_TypeDef* USARTx, uint16_t* pTxBuffer, enum Polling_mechism PollingEn)
{
	if(PollingEn == enable)
		while(!(USARTx->SR & (1<<7)));
	if(USARTx == USART1)
	{
		if(Global_UART_Config[0].Payload_Length == UART_Payload_Length_9B)
		{
			USARTx->DR = (*pTxBuffer & (uint16_t) 0x1FF);
		}
		else
		{
			USARTx->DR = (*pTxBuffer & (uint8_t) 0xFF);
		}
	}
	else if(USARTx == USART2)
	{
		if(Global_UART_Config[1].Payload_Length == UART_Payload_Length_9B)
		{
			USARTx->DR = (*pTxBuffer & (uint16_t) 0x1FF);
		}
		else
		{
			USARTx->DR = (*pTxBuffer & (uint8_t) 0xFF);
		}
	}
	else if(USARTx == USART3)
	{
		if(Global_UART_Config[2].Payload_Length == UART_Payload_Length_9B)
		{
			USARTx->DR = (*pTxBuffer & (uint16_t) 0x1FF);
		}
		else
		{
			USARTx->DR = (*pTxBuffer & (uint8_t) 0xFF);
		}
	}
}


/**================================================================
 * @Fn				- MCAL_UART_SendData
 * @brief			- receive buffer on uart
 * @param [in]		- USARTX: where x can be (1..3 depending on device used)
 * @param [in]		- pTxBuffer Buffer
 * @param [in]		- Polling_mechism PollingEn: Enable pooling or disable it
 * @retval 			- None
 * Note				- None
 */
void MCAL_UART_ReceiveData(USART_TypeDef* USARTx, uint16_t* pRxBuffer, enum Polling_mechism PollingEn)
{
	if(PollingEn == enable)
		while(!(USARTx->SR & (1<<5)));

	if(USARTx == USART1)
	{
		if(Global_UART_Config[0].Payload_Length == UART_Payload_Length_9B)
		{
			if(Global_UART_Config[0].Parity == UART_Parity_NONE)
			{
				*((uint16_t *) pRxBuffer) = USARTx->DR;
			}
			else
			{
				*((uint16_t *) pRxBuffer) = (USARTx->DR & (uint8_t)0xFF);
			}
		}
		else
		{
			if(Global_UART_Config[0].Parity == UART_Parity_NONE)
			{
				*((uint16_t *) pRxBuffer) = (USARTx->DR & (uint8_t)0xFF);
			}
			else
			{
				*((uint16_t *) pRxBuffer) = (USARTx->DR & (uint8_t)0x7F);
			}
		}
	}
	else if(USARTx == USART2)
	{
		if(Global_UART_Config[1].Payload_Length == UART_Payload_Length_9B)
		{
			if(Global_UART_Config[1].Parity == UART_Parity_NONE)
			{
				*((uint16_t *) pRxBuffer) = USARTx->DR;
			}
			else
			{
				*((uint16_t *) pRxBuffer) = (USARTx->DR & (uint8_t)0xFF);
			}
		}
		else
		{
			if(Global_UART_Config[1].Parity == UART_Parity_NONE)
			{
				*((uint16_t *) pRxBuffer) = (USARTx->DR & (uint8_t)0xFF);
			}
			else
			{
				*((uint16_t *) pRxBuffer) = (USARTx->DR & (uint8_t)0x7F);
			}
		}
	}
	else if(USARTx == USART3)
	{
		if(Global_UART_Config[2].Payload_Length == UART_Payload_Length_9B)
		{
			if(Global_UART_Config[2].Parity == UART_Parity_NONE)
			{
				*((uint16_t *) pRxBuffer) = USARTx->DR;
			}
			else
			{
				*((uint16_t *) pRxBuffer) = (USARTx->DR & (uint8_t)0xFF);
			}
		}
		else
		{
			if(Global_UART_Config[2].Parity == UART_Parity_NONE)
			{
				*((uint16_t *) pRxBuffer) = (USARTx->DR & (uint8_t)0xFF);
			}
			else
			{
				*((uint16_t *) pRxBuffer) = (USARTx->DR & (uint8_t)0x7F);
			}
		}
	}

}



/**================================================================
 * @Fn				- MCAL_UART_WAIT_TC
 * @brief			- reset EXTI Registers and NVIC corresponding IRQ MASK
 * @retval 			- None
 * Note				- None
 */
void MCAL_UART_WAIT_TC(USART_TypeDef* USARTx)
{
	while(!(USARTx->SR & (1<<6)));
}






// ISR
void USART1_IRQHandler(void)
{
	Global_UART_Config[0].P_IRQ_CallBack();
}

void USART2_IRQHandler(void)
{
	Global_UART_Config[1].P_IRQ_CallBack();
}

void USART3_IRQHandler(void)
{
	Global_UART_Config[2].P_IRQ_CallBack();
}
