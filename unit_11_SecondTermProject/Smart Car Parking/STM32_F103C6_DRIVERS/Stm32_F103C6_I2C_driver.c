/*
 * Stm32_F103C6_I2C_driver.c
 *
 *  Created on: 10 Nov 2023
 *      Author: Lenovo
 */

#include "Stm32_F103C6_I2C_driver.h"
#include "Stm32_F103C6_gpio_driver.h"


/*
 * ==================================================================================
 *										Generic Variables
 * ==================================================================================
 */
I2C_InitTypeDef Global_I2C_Config[2] = {{0}, {0}};


/*
 * ==================================================================================
 *										Generic Macros
 * ==================================================================================
 */
#define 	I2C1_INDEX						0
#define 	I2C2_INDEX						1


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
 * @Fn				- MCAL_I2C_Init
 * @brief			- Initialises I2C
 * @param [in]		- I2CX: where x can be (1..2 depending on device used)
 * @param [in]		- I2C_InitStruct: All I2C configuration
 * @retval 			- None
 * Note				- Support Standard Mode only
 */
void MCAL_I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct)
{
	uint16_t tmpreg = 0, freqrange = 0, result = 0;
	uint32_t pclk1 = 8000000;
	//Enable RCC Clock
	if(I2Cx == I2C1)
	{
		Global_I2C_Config[I2C1_INDEX] = *I2C_InitStruct;
		RCC_I2C1_CLOCK_EN();
	}
	else
	{
		Global_I2C_Config[I2C2_INDEX] = *I2C_InitStruct;
		RCC_I2C2_CLOCK_EN();
	}

	if(I2C_InitStruct->I2C_Mode == I2C_Mode_I2C)
	{
		/*--------------------------------INIT Timing----------------------------*/
		tmpreg = I2Cx->I2C_CR2;

		tmpreg &= ~(I2C_CR2_FREQ_Msk);

		pclk1 = MCAL_RCC_GetPCLK1Freq();

		freqrange = (uint16_t)(pclk1 / 1000000);

		tmpreg |= freqrange;

		I2Cx->I2C_CR2 = tmpreg;

		// configure CCR
		I2Cx->I2C_CR1 &= ~(I2C_CR1_PE);

		tmpreg = 0;

		if((I2C_InitStruct->I2C_Clock_Speed == I2C_SCLK_SM_50K) || (I2C_InitStruct->I2C_Clock_Speed == I2C_SCLK_SM_100K))
		{
			/* Standard mode CCR Calculations */
			result = (uint16_t)(pclk1 / (I2C_InitStruct->I2C_Clock_Speed << 1));
			tmpreg |= result;
			I2Cx->I2C_CCR = tmpreg;

			/* Rise Time Configuration */
			I2Cx->I2C_TRISE = freqrange + 1;
		}
		else
		{
			// not supported
		}

		/*-----------------------------------I2Cx CR1 configuration-------------------------------*/
		tmpreg = I2Cx->I2C_CR1;

		tmpreg |= (uint16_t)(I2C_InitStruct->I2C_ACK_Control | I2C_InitStruct->General_Call_Address_Detection | I2C_InitStruct->I2C_Mode | I2C_InitStruct->StretchMode);

		I2Cx->I2C_CR1 = tmpreg;


		/*-----------------------------------I2Cx OAR1 and OAR2 configuration-------------------------------*/

		tmpreg = 0;
		if(I2C_InitStruct->I2C_Slave_Address.Enable_Dual_ADD_ack == 1)
		{
			tmpreg = I2C_OAR2_ENDUAL;
			tmpreg |= I2C_InitStruct->I2C_Slave_Address.Secondary_slave_address << I2C_OAR2_ADD2_Pos;
			I2Cx->I2C_OAR2 = tmpreg;


		}
		tmpreg = 0;
		tmpreg |= I2C_InitStruct->I2C_Slave_Address.Primary_slave_address << 1;
		tmpreg |= I2C_InitStruct->I2C_Slave_Address.I2C_Addressing_Slave_mode;
		I2Cx->I2C_OAR1 = tmpreg;

	}
	else
	{
		// SMBus not supported
	}



	// interrupt mode (slave) // check callback pointer  != NULL
	if(I2C_InitStruct->P_Slave_Event_CallBack != NULL)
	{
		// Enable IRQ
		I2Cx->I2C_CR2 |= (I2C_CR2_ITERREN);
		I2Cx->I2C_CR2 |= (I2C_CR2_ITEVTEN);
		I2Cx->I2C_CR2 |= (I2C_CR2_ITBUFEN);
		if(I2Cx == I2C1)
		{
			NVIC_IRQ31_I2C1_EV_IRQ_ENABLE();
			NVIC_IRQ32_I2C1_ER_IRQ_ENABLE();
		}
		else if(I2Cx == I2C2)
		{
			NVIC_IRQ33_I2C2_EV_IRQ_ENABLE();
			NVIC_IRQ34_I2C2_ER_IRQ_ENABLE();
		}

		I2Cx->I2C_SR1 = 0;
		I2Cx->I2C_SR2 = 0;
	}

	I2Cx->I2C_CR1 |= I2C_CR1_PE;
}

/**================================================================
 * @Fn				- MCAL_I2C_DInit
 * @brief			- DeInitialises I2C
 * @param [in]		- I2CX: where x can be (1..2 depending on device used)S
 * @retval 			- None
 * Note				- Support Standard Mode only
 */
void MCAL_I2C_DInit(I2C_TypeDef* I2Cx)
{
	if(I2Cx == I2C1)
	{
		NVIC_IRQ31_I2C1_EV_IRQ_DISABLE();
		NVIC_IRQ32_I2C1_ER_IRQ_DISABLE();
		RCC_I2C1_RESET();
	}
	else if(I2Cx == I2C2)
	{
		NVIC_IRQ33_I2C2_EV_IRQ_DISABLE();
		NVIC_IRQ34_I2C2_ER_IRQ_DISABLE();
		RCC_I2C2_RESET();
	}
}


/**================================================================
 * @Fn				- MCAL_I2C_GPIO_Set_Pins
 * @brief			- prepares the pins required to use the I2C
 * @param [in]		- I2CX: where x can be (1..2 depending on device used)S
 * @retval 			- None
 * Note				- Support Standard Mode only
 */
void MCAL_I2C_GPIO_Set_Pins(I2C_TypeDef* I2Cx)
{
	GPIO_PinConfig_t PinCfg;

	if(I2Cx == I2C1)
	{
		// PB6: SCL
		// PB7: SDA
		PinCfg.GPIO_PinNumber = GPIO_PIN_6;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
		PinCfg.GPIO_OUTPUT_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &PinCfg);

		PinCfg.GPIO_PinNumber = GPIO_PIN_7;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
		PinCfg.GPIO_OUTPUT_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &PinCfg);
	}
	else if(I2Cx == I2C2)
	{
		//PB10: SCL
		//PB11: SDA

		PinCfg.GPIO_PinNumber = GPIO_PIN_10;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
		PinCfg.GPIO_OUTPUT_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &PinCfg);

		PinCfg.GPIO_PinNumber = GPIO_PIN_11;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
		PinCfg.GPIO_OUTPUT_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &PinCfg);
	}
}

/**================================================================
 * @Fn				- MCAL_I2C_Master_TX
 * @brief			- The master sends data through the i2c specified
 * @param [in]		- I2CX: where x can be (1..2 depending on device used)S
 * @param [in]		- devAddr: address of the target we send the data to
 * @param [in]		- dataOut: pointer to the buffer holding the data we want to send
 * @param [in]		- dataLen: length of the data cells in the buffer that we want to send from
 * @param [in]		- Stop: to send a stop condition or not
 * @param [in]		- start: is the start a repeated start or a normal start
 * @retval 			- None
 * Note				- Support Standard Mode only
 */
void MCAL_I2C_Master_TX(I2C_TypeDef* I2Cx, uint16_t devAddr, uint8_t* dataOut, uint32_t dataLen, Stop_Condition Stop, Repeated_Start start)
{
	int i = 0;

	I2C_GenerateStart(I2Cx, ENABLE, start);

	while(!I2C_GetFlagStatus(I2Cx, EV5));

	I2C_SendAddress(I2Cx, devAddr, I2C_Direction_Transmitter);

	while(!I2C_GetFlagStatus(I2Cx, EV6));

	while(!I2C_GetFlagStatus(I2Cx, MASTER_BYTE_TRANMITTING));

	for(i = 0; i <dataLen; i++)
	{
		I2Cx->I2C_DR = dataOut[i];

		while(!I2C_GetFlagStatus(I2Cx, EV8));
	}

	if(Stop == With_Stop)
	{
		I2C_GenerateStop(I2Cx, ENABLE);
	}

}



/**================================================================
 * @Fn				- MCAL_I2C_Master_RX
 * @brief			- prepares the pins required to use the I2C
 * @param [in]		- I2CX: where x can be (1..2 depending on device used)S
 * @param [in]		- devAddr: address of the target we receive the data from
 * @param [in]		- dataOut: pointer to the buffer holding the data we receive
 * @param [in]		- dataLen: length of the data cells in the buffer that we want to receive in
 * @param [in]		- Stop: to send a stop condition or not
 * @param [in]		- start: is the start a repeated start or a normal start
 * @retval 			- None
 * Note				- Support Standard Mode only
 */
void MCAL_I2C_Master_RX(I2C_TypeDef* I2Cx, uint16_t devAddr, uint8_t* dataOut, uint32_t dataLen, Stop_Condition Stop, Repeated_Start start)
{
	int i = 0;
	uint8_t INDEX = I2Cx == I2C1 ? I2C1_INDEX: I2C2_INDEX;

	I2C_GenerateStart(I2Cx, ENABLE, start);

	while(!I2C_GetFlagStatus(I2Cx, EV5));

	I2C_SendAddress(I2Cx, devAddr, I2C_Direction_Receive);

	while(!I2C_GetFlagStatus(I2Cx, EV6));

	I2C_AcknowledgeConfig(I2Cx, ENABLE);

	if(dataLen)
	{
		for(i = dataLen; i > 1; i--)
		{
			while(!I2C_GetFlagStatus(I2Cx, EV7));
			*dataOut = I2Cx->I2C_DR;
			dataOut++;
		}

		I2C_AcknowledgeConfig(I2Cx, DISABLE);

	}

	if(Stop == With_Stop)
	{
		I2C_GenerateStop(I2Cx, ENABLE);
	}

	if(Global_I2C_Config[INDEX].I2C_ACK_Control == I2C_Ack_enabled)
	{
		I2C_AcknowledgeConfig(I2Cx, ENABLE);
	}
}




/******************************************Slave*********************************************/
// Slave interrupt mechanism
void MCAL_I2C_SlaveSendData(I2C_TypeDef* I2Cx, uint8_t data)
{
	I2Cx->I2C_DR = data;
}
uint8_t MCAL_I2C_SlaveReceiveData(I2C_TypeDef* I2Cx)
{
	return (uint8_t) I2Cx->I2C_DR;
}

/******************************************Generic APIS*********************************************/
void I2C_GenerateStart(I2C_TypeDef* I2Cx, FunctionalState NewState, Repeated_Start start)
{
	if(start != repeated_start)
	{
		//check if the bus is idle or someone is in control of the bus
		while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
	}

	if(NewState != DISABLE)
	{
		I2Cx->I2C_CR1 |= I2C_CR1_START;
	}
	else
	{
		I2Cx->I2C_CR1 &= ~(I2C_CR1_START);
	}
}


void I2C_GenerateStop(I2C_TypeDef* I2Cx, FunctionalState stop)
{
	if(stop != DISABLE)
	{
		I2Cx->I2C_CR1 |= I2C_CR1_STOP;
	}
	else
	{
		I2Cx->I2C_CR1 &= ~(I2C_CR1_STOP);
	}
}

FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, Status flag)
{
//	volatile uint32_t dummyRead;
	FlagStatus bitstatus = RESET;
	uint32_t flag1 = 0, flag2 = 0;
	uint32_t last_event = 0;


	switch(flag)
	{
	case I2C_FLAG_BUSY:
	{
		if((I2Cx->I2C_SR2) & (I2C_SR2_BUSY))
		{
			bitstatus = SET;
		}
		else
		{
			bitstatus = RESET;
		}
		break;
	}
	case EV5:
	{
		if((I2Cx->I2C_SR1) & (I2C_SR1_SB))
		{
			bitstatus = SET;
		}
		else
		{
			bitstatus = RESET;
		}
		break;
	}
	case EV6:
	{
		if((I2Cx->I2C_SR1) & (I2C_SR1_ADDR))
		{
			bitstatus = SET;
		}
		else
		{
			bitstatus = RESET;
		}
//		dummyRead = I2Cx->I2C_SR2;
		break;
	}
	case MASTER_BYTE_TRANMITTING:
	{
		flag1 = I2Cx->I2C_SR1;
		flag2 = I2Cx->I2C_SR2;
		flag2 = flag2<< 16;
		last_event = (flag1 | flag2)  & ((uint32_t) 0x00FFFFFF);
		if((last_event & flag) == flag)
		{
			bitstatus = SET;
		}
		else
		{
			bitstatus = RESET;
		}
		break;
	}
	case EV8_1:
	case EV8:
	{
		if((I2Cx->I2C_SR1) & (I2C_SR1_TXE))
		{
			bitstatus = SET;
		}
		else
		{
			bitstatus = RESET;
		}
		break;
	}
	case EV7:
	{
		if((I2Cx->I2C_SR1) & (I2C_SR1_RXNE))
		{
			bitstatus = SET;
		}
		else
		{
			bitstatus = RESET;
		}
		break;
	}
	}

	return bitstatus;
}




void I2C_SendAddress(I2C_TypeDef* I2Cx, uint16_t Address, I2C_Direction Direction)
{
	uint8_t INDEX = I2Cx == I2C1 ? I2C1_INDEX: I2C2_INDEX;

	if(Global_I2C_Config[INDEX].I2C_Slave_Address.I2C_Addressing_Slave_mode == I2C_Addressing_Slave_mode_7bit)
	{
		Address = (Address << 1);
		if(Direction != I2C_Direction_Transmitter)
		{
			Address |= 1<<0;
			I2Cx->I2C_DR = Address;
		}
		else
		{
			Address &= ~(1<<0);
			I2Cx->I2C_DR = Address;

		}

	}
	else
	{
		// not supported
	}
}


void I2C_AcknowledgeConfig(I2C_TypeDef* I2Cx, FunctionalState NewState)
{

	if(NewState == ENABLE)
	{
		I2Cx->I2C_CR1 |= (I2C_CR1_ACK);
	}
	else
	{
		I2Cx->I2C_CR1 &= ~(I2C_CR1_ACK);
	}
}


/************************************************************************************/
// =========================ISR=======================================
/************************************************************************************/

void I2C1_EV_IRQHandler(void)        			/* I2C1 event interrupt                             */
{
//	volatile uint32_t dummy_read = 0;
//	I2C_TypeDef* I2Cx = I2C1;
//
//	uint32_t temp1, temp2, temp3;
//
//	temp1 = I2Cx->I2C_CR2 & (I2C_CR2_ITEVTEN);
//
//	temp2 = I2Cx->I2C_CR2 & (I2C_CR2_ITBUFEN);
//
//	temp3 = I2Cx->I2C_SR1 & (I2C_SR1_STOPF);
}
void I2C1_ER_IRQHandler(void)        			/* I2C1 error interrupt                             */
{

}
void I2C2_EV_IRQHandler(void)        			/* I2C2 event interrupt                             */
{

}
void I2C2_ER_IRQHandler(void)        			/* I2C1 error interrupt                             */
{

}


