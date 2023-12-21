/*
 * UART.c
 *
 * Created: 18/12/2023 16:29:32
 *  Author: Lenovo
 */ 
#include "UART.h"

#include <avr/io.h>
#include <avr/interrupt.h>


static unsigned char* TX_str = (void *) 0;
static unsigned char flag_send = 1;

static unsigned char* RX_str = (void *) 0;
static unsigned char flag_recv = 1;
static volatile unsigned char RX_str_complete = 0;


void UART_Init(void)
{
	// baudrate
	UBRRL = 51;
	
	// normal mode
	CLEAR_BIT(UCSRA, U2X);
	
	//frame
		//no parity
		// 8 bit is initial value by default
	UCSRC |= (1<<UCSZ1) | (1<<UCSZ0) | (1<<URSEL);
	
	//Enable
	SET_BIT(UCSRB, TXEN);
	SET_BIT(UCSRB, RXEN);
}

void UART_Send(unsigned char data)
{
	while(!(UCSRA & (1<<UDRE)));
	UDR = data;
}

unsigned char UART_Receive(void)
{
	while(!READ_BIT(UCSRA, RXC));
	return UDR;
}

void UART_Send_Int32(unsigned long number)
{
	unsigned char* ptr = &number;
	UART_Send(ptr[0]);
	UART_Send(ptr[1]);
	UART_Send(ptr[2]);
	UART_Send(ptr[3]);
}


unsigned long UART_Receive_Int32(void)
{
	unsigned long number = 0;
	unsigned char* ptr = &number;
	ptr[0] = UART_Receive();
	ptr[1] = UART_Receive();
	ptr[2] = UART_Receive();
	ptr[3] = UART_Receive();
	return number;
}

void UART_Send_String(char *buffer)
{
	while(*buffer != '\0')
	{
		UART_Send(*buffer++);
	}
	UART_Send(DefaultStop);
}

void UART_Receive_String(unsigned char *buffer)
{	
	*buffer = UART_Receive();
	while(*buffer != DefaultStop)
	{
		buffer++;
		*buffer = UART_Receive();
	}
	*buffer = '\0';
}


void UART_SendNoBlock(unsigned char data)
{
	UDR = data;
}

unsigned char UART_ReceiveNoBlock(void)
{
	return UDR;
}


void UART_RX_InterruptEnable(void)
{
	SET_BIT(UCSRB, RXCIE);
}

void UART_RX_InterruptDisable(void)
{
	CLEAR_BIT(UCSRB, RXCIE);
}


void UART_TX_InterruptEnable(void)
{
	SET_BIT(UCSRB, TXCIE);
}

void UART_TX_InterruptDisable(void)
{
	CLEAR_BIT(UCSRB, TXCIE);
}


void UART_SendStringAsynch(unsigned char* str)
{
	if(flag_send == 1)
	{
		UART_TX_InterruptEnable();
		UART_SendNoBlock(str[0]);
		TX_str = str;
		flag_send = 0;
	}
	
}


void UART_RecvStringAsynch(unsigned char* str , volatile char** rec_done)
{
	
	// this function is almost complete 
	// my only problem is i want to let the user know if recieve for the string is complete or not
	// so i added a pointer to pointer but the problem that the user can change that data and it doesn't change here in the code until a char is recieved after the recieved string
	//i though of a solution now but i am a bit lazy to implement it
	// i will add a new function let's call it  RecvStringAsynch_Check and it will check if a whole string is recieved or not 
	// here is a psuedo code
	/*
		temp = RX_str_complete
		if(RX_str_complete == 1)
			reset RX_str_complete to 0
		otherwise leave it as it is
		return temp
	*/
	// so the above code will let the user know at least once it has a complete string, the problem will arise if a multiple strings are recieved without the user checking 
	// but i think this is the user's problem or the user should give a string that has a completed string or string other than the buffer we take as argument
	// i though of another solution is that after a whole string is recieved it will be added to queue implemented by linked list, i know that
	// linked list has issues of memory allocation but according to the application we add restriction or modifcation to the implementation of the linked list
	// or just make a multi dimenional array where the string size is already known and we have like 20 strings every string has like 20 charachters only including
	// the null charachter

	if(flag_recv == 1)
	{
		UART_RX_InterruptEnable();
		RX_str = str;
		flag_recv = 0;
		RX_str_complete = 0;
		*rec_done = &RX_str_complete; 
	}
	
}

unsigned char UART_Receive_PerodicCheck(unsigned char *ptr)
{
	if(READ_BIT(UCSRA, RXC))
	{
		*ptr = UDR;
		return 1;
	}
	return 0;
}


ISR(USART_TXC_vect)
{
	static unsigned char i = 1;
	if(TX_str[i] != '\0')
	{
		UART_SendNoBlock(TX_str[i]);
		i++;
	}
	else
	{
		i = 1;
		flag_send = 1;
	}
}

ISR(USART_RXC_vect)
{
	static unsigned char i = 0;
	RX_str[i] = UART_ReceiveNoBlock();
	if(RX_str[i] != DefaultStop)
	{
		RX_str_complete = 0;
		i++;
	}
	else
	{
		RX_str[i] = '\0';
		i = 0;
		flag_recv = 1;
		RX_str_complete = 1;
		
	}
}