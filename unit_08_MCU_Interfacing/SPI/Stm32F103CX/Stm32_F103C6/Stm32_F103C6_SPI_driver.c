/*
 * Stm32_F103C6_USART_driver.c
 *
 *  Created on: 8 Sep 2023
 *      Author: Lenovo
 */

#include "Stm32_F103C6_SPI_driver.h"
#include "Stm32_F103C6_gpio_driver.h"


/*
 * ==================================================================================
 *										Generic Variables
 * ==================================================================================
 */

SPI_Config*	Global_SPI_Config[2] = {NULL, NULL};


/*
 * ==================================================================================
 *										Generic Macros
 * ==================================================================================
 */

#define SPI1_INDEX						0
#define SPI2_INDEX						1

#define SPI_SR_TXE						((uint8_t) 0x02)
#define SPI_SR_RXNE						((uint8_t) 0x01)

/*
 * ==================================================================================
 *										Generic Functions
 * ==================================================================================
 */





/*
 * ==================================================================================
 *									APIs Supported by "MCAL SPI DRIVER"
 * ==================================================================================
 */


/**================================================================
 * @Fn				- MCAL_SPI_Init
 * @brief			- Initializes SPI
 * @param [in]		- SPIX: where x can be (1..3 depending on device used)
 * @param [in]		- SPI_Config: All SPI configuration
 * @retval 			- None
 * Note				- Support for SPI Full Duplex Master/Salve only
 */
void MCAL_SPI_Init(SPI_TypeDef* SPIx, SPI_Config* SPI_Config)
{
	//Safety for registers
	//we will change those variables then set the CR1 and CR2 registers with the value of those
	//variables because if we change them bit by bit, the spi buffers can start receiving or sending incorrect data
	uint16_t tmpreg_CR1 = 0;
	uint16_t tmpreg_CR2 = 0;


	if( SPIx == SPI1)
	{
		Global_SPI_Config[SPI1_INDEX] = SPI_Config;
		RCC_SPI1_CLK_EN();
	}
	else if(SPIx == SPI2)
	{
		Global_SPI_Config[SPI2_INDEX] = SPI_Config;
		RCC_SPI2_CLK_EN();
	}

	// Enable spi
	tmpreg_CR1 = (0x1U<<6);

	// Master or slave
	tmpreg_CR1 |= SPI_Config->Device_Mode;

	// SPI Communication mode
	tmpreg_CR1 |= SPI_Config->Communication_Mode;

	// Frame format
	tmpreg_CR1 |= SPI_Config->Frame_Format;

	// Data Size
	tmpreg_CR1 |= SPI_Config->DataSize;

	// Clock Polarity
	tmpreg_CR1 |= SPI_Config->ClkPolarity;

	// Clock phase
	tmpreg_CR1 |= SPI_Config->ClkPhase;

	//=======================================NSS====================================
	if(SPI_Config-> NSS == SPI_NSS_Hard_Master_SS_output_enable)
	{
		tmpreg_CR2 |= SPI_Config->NSS;
	}
	else if(SPI_Config-> NSS == SPI_NSS_Hard_Master_SS_output_disable)
	{
		tmpreg_CR2 &= SPI_Config->NSS;
	}
	else
	{
		tmpreg_CR1 |= SPI_Config->NSS;
	}

	// SPI_BAUDRATEPRESCALER
	tmpreg_CR1 |= SPI_Config->SPI_BAUDRATEPRESCALER;


	if(SPI_Config->IRQ_Enable != SPI_IRQ_Enable_None)
	{
		tmpreg_CR2 |= SPI_Config->IRQ_Enable;

		if(SPIx == SPI1)
		{
			NVIC_IRQ35_SPI1_Enable;
		}
		else if (SPIx == SPI2)
		{
			NVIC_IRQ36_SPI2_Enable;
		}
	}

	SPIx->SPI_CR1 = tmpreg_CR1;
	SPIx->SPI_CR2 = tmpreg_CR2;

}


/**================================================================
 * @Fn				- MCAL_SPI_DeInit
 * @brief			- Deinitializes SPI
 * @param [in]		- SPIX: where x can be (1..3 depending on device used)
 * @retval 			- None
 * Note				- Support for SPI Full Duplex Master/Salve only
 */
void MCAL_SPI_DeInit(SPI_TypeDef* SPIx)
{
	if(SPIx == SPI1)
	{
		NVIC_IRQ35_SPI1_Disable;
		RCC_SPI1_Reset();
	}
	else if (SPIx == SPI2)
	{
		NVIC_IRQ36_SPI2_Disable;
		RCC_SPI2_Reset();
	}
}


/**================================================================
 * @Fn				- MCAL_SPI_SendData
 * @brief			- send buffer on SPI
 * @param [in]		- SPIx: where x can be (1..3 depending on device used)
 * @param [in]		- pTxBuffer Buffer
 * @param [in]		- PollingMechism PollingEn: Enable pooling or disable it
 * @retval 			- None
 * Note				- None
 */
void MCAL_SPI_SendData(SPI_TypeDef* SPIx, uint16_t* pTxBuffer, enum PollingMechism PollingEn)
{
	//to do recieve only
	if(PollingEn == Pollingenable)
	{
		while( !(SPIx->SPI_SR & SPI_SR_TXE));
	}

	SPIx->SPI_DR = *pTxBuffer;

}


/**================================================================
 * @Fn				- MCAL_SPI_RecieveData
 * @brief			- receive buffer from SPI
 * @param [in]		- SPIx: where x can be (1..3 depending on device used)
 * @param [in]		- pTxBuffer Buffer
 * @param [in]		- PollingMechism PollingEn: Enable pooling or disable it
 * @retval 			- None
 * Note				- None
 */
void MCAL_SPI_ReceiveData(SPI_TypeDef* SPIx, uint16_t* pRxBuffer, enum PollingMechism PollingEn)
{

	if(PollingEn == Pollingenable)
	{
		while( !(SPIx->SPI_SR & SPI_SR_RXNE));
	}

	*pRxBuffer = SPIx->SPI_DR;

}

/**================================================================
 * @Fn				- MCAL_SPI_TX_RX(
 * @brief			- send and receive using from SPI
 * @param [in]		- SPIx: where x can be (1..3 depending on device used)
 * @param [in]		- pTxBuffer Buffer
 * @param [in]		- PollingMechism PollingEn: Enable pooling or disable it
 * @retval 			- None
 * Note				- None
 */
void MCAL_SPI_TX_RX(SPI_TypeDef* SPIx, uint16_t* pTxBuffer, enum PollingMechism PollingEn)
{
	if(PollingEn == Pollingenable)
		while( !(SPIx->SPI_SR & SPI_SR_TXE));
	SPIx->SPI_DR = *pTxBuffer;

	if(PollingEn == Pollingenable)
		while( !(SPIx->SPI_SR & SPI_SR_RXNE));
	*pTxBuffer = SPIx->SPI_DR;

}



/**================================================================
 * @Fn				- MCAL_SPI_GPIO_Set_Pins
 * @brief			- prepares the pins needed for the spi using
 * @param [in]		- SPIX: where x can be (1..3 depending on device used)
 * @retval 			- None
 * Note				- Support for SPI Full Duplex Master/Salve only
 */
void MCAL_SPI_GPIO_Set_Pins(SPI_TypeDef* SPIx)
{
	GPIO_PinConfig_t PinCfg;
	if(SPIx == SPI1)
	{
		//		PA4: SPI1_NSS
		//		PA5: SPI1_ٍSCK
		//		PA6: SPI1_MISO
		//		PA7: SPI1_MOSI

		if(Global_SPI_Config[SPI1_INDEX]->Device_Mode == SPI_Device_Mode_Master)
		{
			//		PA4: SPI1_NSS
			switch(Global_SPI_Config[SPI1_INDEX]->NSS)
			{
			case SPI_NSS_Hard_Master_SS_output_disable:
				PinCfg.GPIO_PinNumber = GPIO_PIN_4;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
				break;

			case SPI_NSS_Hard_Master_SS_output_enable:
				PinCfg.GPIO_PinNumber = GPIO_PIN_4;
				PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
				PinCfg.GPIO_OUTPUT_Speed = GPIO_SPEED_10M;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
				break;
			}

			//		PA5: SPI1_ٍSCK
			PinCfg.GPIO_PinNumber = GPIO_PIN_5;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_OUTPUT_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			//		PA6: SPI1_MISO
			PinCfg.GPIO_PinNumber = GPIO_PIN_6;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			//		PA7: SPI1_MOSI
			PinCfg.GPIO_PinNumber = GPIO_PIN_7;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_OUTPUT_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

		}
		else	//Slave
		{
			//		PA4: SPI1_NSS
			if(Global_SPI_Config[SPI1_INDEX]->NSS == SPI_NSS_Hard_Slave)
			{
				PinCfg.GPIO_PinNumber = GPIO_PIN_4;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
			}
			//		PA5: SPI1_ٍSCK
			PinCfg.GPIO_PinNumber = GPIO_PIN_5;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			//		PA6: SPI1_MISO
			PinCfg.GPIO_PinNumber = GPIO_PIN_6;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_OUTPUT_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			//		PA7: SPI1_MOSI
			PinCfg.GPIO_PinNumber = GPIO_PIN_7;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}
	}
	else if(SPIx == SPI2)
	{
		//		PB12: SPI1_NSS
		//		PB13: SPI1_ٍSCK
		//		PB14: SPI1_MISO
		//		PB15: SPI1_MOSI
		if(Global_SPI_Config[SPI2_INDEX]->Device_Mode == SPI_Device_Mode_Master)
		{
			//		PB12: SPI1_NSS
			switch(Global_SPI_Config[SPI2_INDEX]->NSS)
			{
			case SPI_NSS_Hard_Master_SS_output_disable:
				PinCfg.GPIO_PinNumber = GPIO_PIN_12;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOB, &PinCfg);
				break;

			case SPI_NSS_Hard_Master_SS_output_enable:
				PinCfg.GPIO_PinNumber = GPIO_PIN_12;
				PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
				PinCfg.GPIO_OUTPUT_Speed = GPIO_SPEED_10M;
				MCAL_GPIO_Init(GPIOB, &PinCfg);
				break;
			}

			//		PB13: SPI1_ٍSCK
			PinCfg.GPIO_PinNumber = GPIO_PIN_13;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_OUTPUT_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

			//		PB14: SPI1_MISO
			PinCfg.GPIO_PinNumber = GPIO_PIN_14;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

			//		PB15: SPI1_MOSI
			PinCfg.GPIO_PinNumber = GPIO_PIN_15;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_OUTPUT_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

		}
		else	//Slave
		{
			//		PB12: SPI1_NSS
			if(Global_SPI_Config[SPI2_INDEX]->NSS == SPI_NSS_Hard_Slave)
			{
				PinCfg.GPIO_PinNumber = GPIO_PIN_12;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOB, &PinCfg);
			}
			//		PB13: SPI1_ٍSCK
			PinCfg.GPIO_PinNumber = GPIO_PIN_13;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

			//		PB14: SPI1_MISO
			PinCfg.GPIO_PinNumber = GPIO_PIN_14;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_OUTPUT_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

			//		PB15: SPI1_MOSI
			PinCfg.GPIO_PinNumber = GPIO_PIN_15;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &PinCfg);
		}
	}
}



// =========================ISR=======================================

void SPI1_IRQHandler(void)
{
	struct S_IRQ_SRC irq_src;
	irq_src.TXE = ((SPI1->SPI_SR & (1<<1)) >> 1);
	irq_src.RXNE = ((SPI1->SPI_SR) & (1<<0) >> 0);
	irq_src.ERRI = ((SPI1->SPI_SR) & (1<<4) >> 4);
	Global_SPI_Config[SPI1_INDEX]->P_IRQ_CallBack(irq_src);
}


void SPI2_IRQHandler(void)
{
	struct S_IRQ_SRC irq_src;
	irq_src.TXE = ((SPI2->SPI_SR & (1<<1)) >> 1);
	irq_src.RXNE = ((SPI2->SPI_SR) & (1<<0) >> 0);
	irq_src.ERRI = ((SPI2->SPI_SR) & (1<<4) >> 4);
	Global_SPI_Config[SPI2_INDEX]->P_IRQ_CallBack(irq_src);
}

