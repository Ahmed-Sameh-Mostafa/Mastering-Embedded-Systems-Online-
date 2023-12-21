/*
 * Stm32_F103C6_USART_driver.h
 *
 *  Created on: 8 Sep 2023
 *      Author: Lenovo
 */

#ifndef INC_STM32_F103C6_SPI_DRIVER_H_
#define INC_STM32_F103C6_SPI_DRIVER_H_

#include "stm32_f103x6.h"
#include "Stm32_F103C6_gpio_driver.h"
#include "Stm32_F103C6_RCC_driver.h"


// configuration structure

struct S_IRQ_SRC
{
	uint8_t TXE:1;		//TX buffer empty interrupt
	uint8_t RXNE:1;		//RX buffer not empty interrupt
	uint8_t ERRI; 		//Error Interrupt
	uint8_t Reserved:5;
};

typedef struct
{

	uint16_t Device_Mode; 					//specifies the spi operating mode @ref SPI_Device_Mode

	uint16_t Communication_Mode;			//specifies the spi bidrectional mode state @ref SPI_Communication_Mode

	uint16_t Frame_Format;					//specifies LSB or MSB @ref SPI_Frame_Format

	uint16_t DataSize;						// @ref SPI_DataSize

	uint16_t ClkPolarity;					// @ref SPI_ClkPolarity

	uint16_t ClkPhase;						// @ref SPI_ClkPhase

	uint16_t NSS;							// @ref SPI_NSS

	uint16_t SPI_BAUDRATEPRESCALER;			// @ref SPI_BAUDRATEPRESCALER

	uint16_t IRQ_Enable;					// @ref SPI_IRQ_Enable

	void (* P_IRQ_CallBack)(struct S_IRQ_SRC irq_src);	//set the c function which will be called once the irq happen

}SPI_Config;

/*------------------------------------------------------------------*/
/* 							Reference Macros						*/
/*------------------------------------------------------------------*/

//@ref SPI_Device_Mode
#define SPI_Device_Mode_Slave					(0x00000000U)
#define SPI_Device_Mode_Master					(0x1U << 2)

//@ref SPI_Communication_Mode
#define SPI_DIRECTION_2LINES					(0x00000000U)
#define SPI_DIRECTION_2LINES_RXONLY				(0x1U << 10)
#define SPI_DIRECTION_1LINES_receive_only		((0x1U << 15))
#define SPI_DIRECTION_1LINES_transmit_only		((0x1U << 15) | (0x1U << 14))

//@ref SPI_Frame_Format
#define SPI_Frame_Format_MSB_transmitted_first	(0x00000000U)
#define SPI_Frame_Format_LSB_transmitted_first	(0x1U << 7)

//@ref SPI_DataSize
#define SPI_DataSize_8BIT						(0x00000000U)
#define SPI_DataSize_16BIT						(0x1U << 11)

//@ref SPI_ClkPolarity
#define SPI_ClkPolarity_LOW_when_idle			(0x00000000U)
#define SPI_ClkPolarity_HIGH_when_idle			(0x1U << 1)


//@ref SPI_ClkPhase
#define SPI_Clock_Phase_1EDGE_first_data_capture_edge		(0x00000000U)
#define SPI_Clock_Phase_2EDGE_first_data_capture_edge		(0x1U << 0)

//@ref SPI_NSS		Slave Select Managment
//===============================NSS================================

//Hardware
#define SPI_NSS_Hard_Slave						(0x00000000U)
#define SPI_NSS_Hard_Master_SS_output_enable	(0x1U<<2)
#define SPI_NSS_Hard_Master_SS_output_disable	~(0x1U<<2)

//Software	Master or slave
#define SPI_NSS_Soft_NSSInternalSoft_Reset		(0x1U<<9)
#define SPI_NSS_Soft_NSSInternalSoft_Set		((0x1U<<9) | (0x1U<<8))



//@ref SPI_BAUDRATEPRESCALER
#define SPI_BAUDRATEPRESCALER_2					(0x00000000U)
#define SPI_BAUDRATEPRESCALER_4					(0b001U  << 3)
#define SPI_BAUDRATEPRESCALER_8					(0b010U  << 3)
#define SPI_BAUDRATEPRESCALER_16				(0b011U  << 3)
#define SPI_BAUDRATEPRESCALER_32				(0b100U  << 3)
#define SPI_BAUDRATEPRESCALER_64				(0b101U  << 3)
#define SPI_BAUDRATEPRESCALER_128				(0b110U  << 3)
#define SPI_BAUDRATEPRESCALER_256				(0b111U  << 3)


//@ref SPI_IRQ_Enable
#define SPI_IRQ_Enable_None						(0x00000000U)
#define SPI_IRQ_Enable_TXEIE					(0x1UL<<7)
#define SPI_IRQ_Enable_RXNEIE					(0x1UL<<6)
#define SPI_IRQ_Enable_ERRIE					(0x1UL<<5)

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
enum PollingMechism{
	Pollingenable,
	Pollingdisable
};



/************************************************************************************/
/************************************************************************************/
/************************************************************************************/

/*
 * ==================================================================================
 *									APIs Supported by "MCAL SPI DRIVER"
 * ==================================================================================
 */


void MCAL_SPI_Init(SPI_TypeDef* SPIx, SPI_Config* SPI_Config);
void MCAL_SPI_DeInit(SPI_TypeDef* SPIx);

void MCAL_SPI_GPIO_Set_Pins(SPI_TypeDef* SPIx);

void MCAL_SPI_SendData(SPI_TypeDef* SPIx, uint16_t* pTxBuffer, enum PollingMechism PollingEn);
void MCAL_SPI_ReceiveData(SPI_TypeDef* SPIx, uint16_t* pRxBuffer, enum PollingMechism PollingEn);


void MCAL_SPI_TX_RX(SPI_TypeDef* SPIx, uint16_t* pTxBuffer, enum PollingMechism PollingEn);

#endif /* INC_STM32_F103C6_USART_DRIVER_H_ */
