#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


/*===============Learn in depth================*/
/*===Second term project Smart Car Barking=====*/
/*Completed by Eng : Ahmed Sameh Elshahed*/

/*In this project i achieved the following
 * 			I found and fixed some bugs in my gpio and uart drivers that were written while during unit 8 lectures.
 * 			I modified the lcd driver(Made by Eng Mostafa) a little bit to make every line starts 0 position(modified gotoXy function).
 * 			I followed the flow chart given by Eng Mostafa to get the same behaviour while testing in proteus.
 * 			I modified the keypad to my own version as i thought the errors was from there but it was from my gpio driver :(
 */

//=================================================================

//		Add Your Drivers



#include "STM32_F103C6.h"
#include "Stm32_F103C6_gpio_driver.h"
#include "LCD_ME.h"
#include "Stm32_F103C6_USART_driver.h"
#include "Keypad.h"


//=================================================================




#include "Servo_Motor.h"

// Leds
#define Grn_led_pin GPIO_PIN_11
#define Red_led_pin	GPIO_PIN_0

#define Led_port	GPIOA
#define Led_off 	GPIO_PIN_SET
#define Led_on		GPIO_PIN_RESET

// PIRs
#define Entry_pir_pin 	GPIO_PIN_7
#define Exit_pir_pin	GPIO_PIN_1

#define Pir_port		GPIOA

/*=================Global Variables===============*/
uint16_t RFID_CARD_Enter = 0; 	// 	0 means no id is in the card reader, as 0 can't be an ID
uint16_t RFID_CARD_EXIT = 0; 	//	0 means no id is in the card reader, as 0 can't be an ID

uint8_t pass[3] ={0};

unsigned char Available_Slots='3';
uint8_t Search_Done = 0;



void RFID_CARD_Enter_CallBack(void);
void RFID_CARD_EXIT_CallBack(void);

void LCD_Welcome(void);
void LCD_Display_Empty_Slots(void);
void LEDs_Init(void);
void PIRs_Iint(void);
void Store_IDs_From_Admin(void);


// This LCD is for the Admin's LCD
s_LCD_Config_t LCD={

/*
	s_LCDCtrlPins_t s_LCDCtrlPins; 		GPiox, rspin, en pin
	s_LCDDataPins_t	s_LCDDataPins ; 	Gpiox, lowest data pin ie D4 in 4-bit mode, D0 in 8-bit mode
	e_EntryMode_t	e_EntryMode; 		No shift increment 2
	e_DispCtrl_t	e_DispCtrl; 		ONDISP_BLINKCURSOR
	e_OperMode_t	e_OperMode; 		FOURBIT_2LINE_7DOT
	uint8_t 		Ch_Counter;			0
*/
		{GPIOB, GPIO_PIN_11, GPIO_PIN_10},
		{GPIOB, GPIO_PIN_12},
		NOSHIFT_INCREMENT,
		ONDISP_BLINKCURSOR,
		FOURBIT_2LINE_7DOT,
		0

};


//While this LCD configuration is used for the incoming Cars and as a Welcome Dash board
s_LCD_Config_t LCD2={
/*
	s_LCDCtrlPins_t s_LCDCtrlPins; 		{GPiox, rspin, en pin}, a structure can be initialised directly this way
	s_LCDDataPins_t	s_LCDDataPins ; 	Gpiox, lowest data pin ie D4 in 4-bit mode, D0 in 8-bit mode
	e_EntryMode_t	e_EntryMode; 		No shift increment 2
	e_DispCtrl_t	e_DispCtrl; 		ONDISP_BLINKCURSOR
	e_OperMode_t	e_OperMode; 		FOURBIT_2LINE_7DOT
	uint8_t 		Ch_Counter;			0
*/
		{GPIOA, GPIO_PIN_5, GPIO_PIN_6},
		{GPIOA, GPIO_PIN_12},
		NOSHIFT_INCREMENT,
		ONDISP_BLINKCURSOR,
		FOURBIT_2LINE_7DOT,
		0
};


int main(void)
{

	RCC_GPIOA_CLOCK_EN();
	RCC_GPIOB_CLOCK_EN();
	RCC_AFIO_CLOCK_EN();
	keypad_Init();

	Timer2_init();
	Servo1_Entry_Gate_Init();
	Servo2_Exit_Gate_Init();
	//==========================UART1 INIT=============================
	/* PA9  TX
	 * PA10 RX
	 * PA11 CTC
	 * PA12 RTS
	 *
	 */

	// from proteus i figured out the next configuration
	UART_Config uart1_cfg = {
			UART_Mode_TX_RX,
			UART_BaudRate_115200,
			UART_Payload_Length_8B,
			UART_Parity_NONE,
			UART_StopBits_1,
			UART_HwFlowCtl_NONE,
			UART_IRQ_Enable_RXNEIE,
			RFID_CARD_Enter_CallBack		};
	MCAL_UART_Init(USART1, &uart1_cfg);
	MCAL_UART_GPIO_Set_Pins(USART1);


	//==========================UART2 INIT=============================
	/* PA2  ->TX
	 * PA3 ->RX
	 * PA0 ->CTS
	 * PA1 ->RTS
	 */

	// I have two options
	// 1- make a new uart cfg variable for uart 2
	// 2- modify the cfg file used for uart 1(same attributes except for the call back function)
	// then reuse it, but for simplicity let's go with first option
	UART_Config uart2_cfg = {
				UART_Mode_TX_RX,
				UART_BaudRate_115200,
				UART_Payload_Length_8B,
				UART_Parity_NONE,
				UART_StopBits_1,
				UART_HwFlowCtl_NONE,
				UART_IRQ_Enable_RXNEIE,
				RFID_CARD_EXIT_CallBack		};
	MCAL_UART_Init(USART2, &uart2_cfg);
	MCAL_UART_GPIO_Set_Pins(USART2);


	LCD_init(&LCD);
	LCD_init(&LCD2);
	LEDs_Init();
	PIRs_Iint();

	/*==========Enter IDs To Store In Array Pass==========*/
	// Assuming All IDs Entered by the Admin are unique
	 Store_IDs_From_Admin();

	/*Dash Bord LCD*/
	LCD_Welcome();
	dms(200);
	LCD_Display_Empty_Slots();
	dms(200);

	int i=0;
	while(1)
	{
		if(Available_Slots>'0')
		{
			LCD_gotoxy(&LCD2, 0, 2);
			LCD_sendstring(&LCD2,"Put Your Id In");
			LCD_gotoxy(&LCD2,0,3 );
			LCD_sendstring(&LCD2,"Card Reader");
			while(RFID_CARD_Enter ==0 && RFID_CARD_EXIT==0); //Wait for Enter any id
		}
		/*======Parking is full so not allow enetr cars=======*/
		else
		{
			LCD_sendchar(&LCD2, 0x0c, COMMAND);
			LCD_sendchar(&LCD2, 0x01, COMMAND);
			LCD_gotoxy(&LCD2, 0, 0);
			LCD_sendstring(&LCD2,"Parking Is Full");
			LCD_gotoxy(&LCD2, 0, 1);
			LCD_sendstring(&LCD2,"Entry Not Allowed");
		}

		// searching for an id ID in array of Passwords
		for(i=0;i<3;i++)
		{
			if(RFID_CARD_Enter == pass[i] || RFID_CARD_EXIT == pass[i] )
			{
				Search_Done=1;
			}

		}
		/*=====================Enter gate=====================*/
		if(Search_Done == 1 && RFID_CARD_Enter != 0 && Available_Slots>'0')
		{
			LCD_sendchar(&LCD2, 0x0c, COMMAND);
			LCD_sendchar(&LCD2, 0x01, COMMAND);
			LCD_gotoxy(&LCD2, 0, 0);
			LCD_sendstring(&LCD2,"ID Is Right");
			LCD_gotoxy(&LCD2, 0, 1);
			LCD_sendstring(&LCD2,"Entry gate Opens");

			MCAL_GPIO_WritePin(Led_port, Grn_led_pin, Led_on);
			Servo1_Entry_Gate(UP);
			Available_Slots--;

			RFID_CARD_Enter =0;
			Search_Done =0;

			dms(300);

			while(MCAL_GPIO_ReadPin(Pir_port, Entry_pir_pin))
			{
				dms(200);
			}

			MCAL_GPIO_WritePin(Led_port, Grn_led_pin, Led_off);
			Servo1_Entry_Gate(Down);

			/*Dash Bord LCD*/
			LCD_Welcome();
			dms(200);
			LCD_Display_Empty_Slots();

		}
		/*===================Exit gate====================*/
		if(Search_Done == 1 && RFID_CARD_EXIT !=0 && Available_Slots<'3')
		{
			LCD_sendchar(&LCD2, 0x0c, COMMAND);
			LCD_sendchar(&LCD2, 0x01, COMMAND);
			LCD_gotoxy(&LCD2, 0, 0);
			LCD_sendstring(&LCD2,"ID Is Right");
			LCD_gotoxy(&LCD2, 0, 1);
			LCD_sendstring(&LCD2,"Exit Gate Opens");

			MCAL_GPIO_WritePin(Led_port, Grn_led_pin, Led_on);
			Servo2_Exit_Gate(UP);


			Available_Slots++;
			dms(300);

			while(MCAL_GPIO_ReadPin(Pir_port, Exit_pir_pin))
			{
				dms(200);
			}

			MCAL_GPIO_WritePin(Led_port, Grn_led_pin, Led_off);
			Servo2_Exit_Gate(Down);

			RFID_CARD_EXIT =0;
			Search_Done =0;

			/*Dash Bord LCD*/
			LCD_Welcome();
			dms(200);
			LCD_Display_Empty_Slots();
		}

		/*==================Wrong Id====================*/
		if(Search_Done == 0 && (RFID_CARD_Enter >0 || RFID_CARD_EXIT>0) )
		{
			LCD_sendchar(&LCD2, 0x0c, COMMAND);
			LCD_sendchar(&LCD2, 0x01, COMMAND);
			LCD_gotoxy(&LCD2, 0, 0);
			LCD_sendstring(&LCD2,"Wrong ID");
			LCD_gotoxy(&LCD2, 0, 1);
			LCD_sendstring(&LCD2,"Try Again");

			// alarm turn on and off 3 times
			for(i=0;i<3;i++)
			{
				MCAL_GPIO_WritePin(Led_port, Red_led_pin, Led_on);
				dms(200);
				MCAL_GPIO_WritePin(Led_port, Red_led_pin, Led_off);
			}


			/*Dash Bord LCD*/
			LCD_Welcome();
			dms(150);
			LCD_Display_Empty_Slots();


			RFID_CARD_EXIT  = 0;
			RFID_CARD_Enter = 0;
		}


	}

	return 0;
}


/*Call Back For UART*/
void RFID_CARD_Enter_CallBack(void)
{
	// since we made the uart in TX and RX mode and the interrupt is enabled for non empty Rx
	// we will receive then send the received data again
	// and we will save the data in the global variable that was already made
	MCAL_UART_ReceiveData(USART1, &RFID_CARD_Enter, disable);
	MCAL_UART_SendData(USART1, &RFID_CARD_Enter, enable);

}

void RFID_CARD_EXIT_CallBack(void)
{
	// Similar to the Enter call back
	MCAL_UART_ReceiveData(USART2, &RFID_CARD_EXIT, disable);
	MCAL_UART_SendData(USART2, &RFID_CARD_EXIT, enable);
}



void LCD_Welcome(void)
{
	/*Dash Bord LCD*/

	LCD_sendchar(&LCD2, 0x0c, COMMAND);
	LCD_sendchar(&LCD2, 0x01, COMMAND);
	LCD_gotoxy(&LCD2, 0, 0);
	LCD_sendstring(&LCD2,"Welcome in");
	LCD_gotoxy(&LCD2,0,1 );
	LCD_sendstring(&LCD2,"AS Parking");
}

void LCD_Display_Empty_Slots(void)
{
	LCD_sendchar(&LCD2, 0x0c, COMMAND);
	LCD_sendchar(&LCD2, 0x01, COMMAND);
	LCD_gotoxy(&LCD2, 0, 0);
	LCD_sendstring(&LCD2,"Empty Slots=");
	LCD_gotoxy(&LCD2, 13, 0);
	LCD_sendchar(&LCD2,Available_Slots, DATA);
}

void LEDs_Init(void)
{
	//RED LED A0
	GPIO_PinConfig_t PinCinfg;
	PinCinfg.GPIO_PinNumber= Red_led_pin;
	PinCinfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCinfg.GPIO_OUTPUT_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOA, &PinCinfg);

	//GREEN LED A11
	PinCinfg.GPIO_PinNumber= Grn_led_pin;
	PinCinfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCinfg.GPIO_OUTPUT_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOA, &PinCinfg);
}

void PIRs_Iint(void)
{
	//PIR1 A7			Entry gate
	GPIO_PinConfig_t PinCinfg;
	PinCinfg.GPIO_PinNumber=GPIO_PIN_7;
	PinCinfg.GPIO_MODE = GPIO_MODE_INPUT_PU;
	MCAL_GPIO_Init(GPIOA, &PinCinfg);

	//PIR2 A1			Exit Gate
	PinCinfg.GPIO_PinNumber=GPIO_PIN_1;
	PinCinfg.GPIO_MODE = GPIO_MODE_INPUT_PU;
	MCAL_GPIO_Init(GPIOA, &PinCinfg);

	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, 1); //make A0 ground
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1); //make A11 ground

}

void Store_IDs_From_Admin(void)
{
	uint8_t temp_pass = 'N';
	// 1st Stage: clear screen and display msg to Admin
	//LCD_clearscreen(&LCD);
	LCD_sendchar(&LCD, 0x0c, COMMAND);
	LCD_gotoxy(&LCD, 0, 0);
	LCD_sendstring(&LCD, "Enter Allowed ID");

	// 2nd Stage: display which id is needed (1st Id here) and show the entered id
	LCD_gotoxy(&LCD, 0, 1);
	LCD_sendstring(&LCD, "First ID: ");

	do
	{
		temp_pass = keypad_Read();
	}while(temp_pass == 'N');
	pass[0] = temp_pass;
	LCD_gotoxy(&LCD, 10, 1);
	LCD_sendchar(&LCD, pass[0], DATA);


	// 3rd Stage: display which id is needed (2nd Id here) and show the entered id
	LCD_gotoxy(&LCD, 0, 2);
	LCD_sendstring(&LCD, "Second ID: ");
	temp_pass = 'N';
	do
	{
		temp_pass = keypad_Read();
	}while(temp_pass == 'N');
	pass[1] = temp_pass;
	LCD_gotoxy(&LCD, 10, 2);
	LCD_sendchar(&LCD, pass[1], DATA);

	// 4th Stage: display which id is needed (3rd Id here) and show the entered id
	LCD_gotoxy(&LCD, 0, 3);
	LCD_sendstring(&LCD, "Third ID: ");
	do
	{
		temp_pass = keypad_Read();
	}while(temp_pass == 'N');
	pass[2] = temp_pass;
	LCD_gotoxy(&LCD, 10, 3);
	LCD_sendchar(&LCD, pass[2], DATA);


	// 5th Stage: Show the saved IDs
	LCD_clearscreen(&LCD);
	LCD_gotoxy(&LCD, 0, 0);
	LCD_sendstring(&LCD, "Saved IDs: ");
	for(uint8_t i = 0; i < 3; i++)
	{
		LCD_gotoxy(&LCD, 0, i + 1);
		LCD_sendchar(&LCD, pass[i], DATA);
	}

}
