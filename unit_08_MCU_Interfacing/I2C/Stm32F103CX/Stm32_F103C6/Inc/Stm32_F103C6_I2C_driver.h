/*
 * Stm32_F103C6_I2C_driver.h
 *
 *  Created on: 10 Nov 2023
 *      Author: Lenovo
 */

#ifndef INC_STM32_F103C6_I2C_DRIVER_H_
#define INC_STM32_F103C6_I2C_DRIVER_H_

#include "stm32_f103x6.h"
#include "Stm32_F103C6_gpio_driver.h"
#include "Stm32_F103C6_RCC_driver.h"


// configuration structure

struct S_I2C_Slave_Device_Address
{
	uint16_t Enable_Dual_ADD_ack; 						// 1-enable, 0-disable
	uint16_t Primary_slave_address;
	uint16_t Secondary_slave_address;
	uint32_t I2C_Addressing_Slave_mode; 				//@I2C_Addressing_Slave_mode
};


typedef enum{
	I2C_EV_STOP,
	I2C_ERROR_AF,
	I2C_EV_ADDR_Matched,
	I2C_EV_DATA_REQ,
	I2C_EV_DATA_RCV
}Slave_State;

typedef struct
{
	uint32_t	I2C_Clock_Speed;					// This specifies the clock frequency
													// This parameter must be set to @I2C_SCLK_

	uint32_t	StretchMode;						//@ref @I2C_StretchMode_

	uint32_t	I2C_Mode;							//specifies the i2c mode
													// @ref I2C_Mode

	struct S_I2C_Slave_Device_Address		I2C_Slave_Address;

	uint32_t	I2C_ACK_Control;					//@ref I2C_ACK

	uint32_t	General_Call_Address_Detection;		// @I2C_ENGC

	void		(* P_Slave_Event_CallBack)(Slave_State state)



}I2C_InitTypeDef;

/*------------------------------------------------------------------*/
/* 							Reference Macros						*/
/*------------------------------------------------------------------*/

// @I2C_SCLK_
//		SM only, FM not supported
#define I2C_SCLK_SM_50K									(50000U)
#define I2C_SCLK_SM_100K								(100000U)

// @I2C_StretchMode_
#define I2C_StretchMode_Enabled							(0U)
#define I2C_StretchMode_Disabled						I2C_CR1_NOSTRETCH

// @I2C_Mode
#define I2C_Mode_I2C									(0U)
#define I2C_Mode_SM										 I2C_CR1_SMBUS

// @I2C_Addressing_Slave_mode
#define I2C_Addressing_Slave_mode_7bit					(0x00000000U)
#define I2C_Addressing_Slave_mode_10bit					(uint16_t)(1<<15)

// @I2C_ACK
#define I2C_Ack_enabled									(I2C_CR1_ACK)
#define I2C_Ack_disable									(uint16_t)(0x0000)

// @I2C_ENGC
#define I2C_ENGC_Enable									I2C_CR1_ENGC
#define I2C_ENGC_Disable								(uint16_t)(0x0000)


/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/

typedef enum
{
	With_Stop,
	without_Stop
}Stop_Condition;

typedef enum
{
	Start,
	repeated_start
}Repeated_Start;

typedef enum
{
	DISABLE = 0,
	ENABLE = 1
}FunctionalState;

typedef enum
{
	RESET = 0,
	SET = 1
}FlagStatus;


#define I2C_EVENT_MASTER_BYTE_TRANMITTING			((uint32_t) 0x00070080)

typedef enum
{
		I2C_FLAG_BUSY=0,
		EV5,
		EV6,
		MASTER_BYTE_TRANMITTING = ((uint32_t) 0x00070080),
		EV8,
		EV8_1,
		EV7

}Status;

typedef enum {I2C_Direction_Transmitter = 0, I2C_Direction_Receive = 1} I2C_Direction;


/************************************************************************************/
/************************************************************************************/
/************************************************************************************/

/*
 * ==================================================================================
 *									APIs Supported by "MCAL SPI DRIVER"
 * ==================================================================================
 */

void MCAL_I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct);
void MCAL_I2C_DInit(I2C_TypeDef* I2Cx);

void MCAL_I2C_GPIO_Set_Pins(I2C_TypeDef* I2Cx);

// Master polling mechanism
void MCAL_I2C_Master_TX(I2C_TypeDef* I2Cx, uint16_t devAddr, uint8_t* dataOut, uint32_t dataLen, Stop_Condition Stop, Repeated_Start start);
void MCAL_I2C_Master_RX(I2C_TypeDef* I2Cx, uint16_t devAddr, uint8_t* dataOut, uint32_t dataLen, Stop_Condition Stop, Repeated_Start start);

// Slave interrupt mechanism
void MCAL_I2C_SlaveSendData(I2C_TypeDef* I2Cx, uint8_t data);
uint8_t MCAL_I2C_SlaveReceiveData(I2C_TypeDef* I2Cx);

// Generic APIs
void I2C_GenerateStart(I2C_TypeDef* I2Cx, FunctionalState NewState, Repeated_Start start);
void I2C_GenerateStop(I2C_TypeDef* I2Cx, FunctionalState NewState);

FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, Status flag);

void I2C_SendAddress(I2C_TypeDef* I2Cx, uint16_t Address, I2C_Direction Direction);

void I2C_AcknowledgeConfig(I2C_TypeDef* I2Cx, FunctionalState NewState);

#endif /* INC_STM32_F103C6_I2C_DRIVER_H_ */
