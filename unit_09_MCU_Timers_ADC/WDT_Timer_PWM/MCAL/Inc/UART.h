/*
 * UART.h
 *
 * Created: 18/12/2023 16:29:18
 *  Author: Lenovo
 */ 


#ifndef UART_H_
#define UART_H_

#include "AvrMemoryMap.h"
#include "Utils.h"


#define DefaultStop '\r'
// UCSRA bits
#define U2X			1
#define UDRE		5
#define TXC			6
#define RXC			7

// UCSRB
#define UCSZ2		2
#define TXEN		3
#define RXEN		4
#define UDRIE		5
#define TXCIE		6
#define RXCIE		7


// UCSRC
#define UCSZ0		1
#define UCSZ1		2
#define URSEL		7

void UART_Init(void);

void UART_Send(unsigned char data);
unsigned char UART_Receive(void);

void UART_Send_Int32(unsigned long);
unsigned long UART_Receive_Int32(void);

void UART_Send_String(char *buffer);
void UART_Receive_String(unsigned char *buffer);

void UART_SendNoBlock(unsigned char data);
unsigned char UART_ReceiveNoBlock(void);

void UART_RX_InterruptEnable(void);
void UART_RX_InterruptDisable(void); 

void UART_TX_InterruptEnable(void);
void UART_TX_InterruptDisable(void);

void UART_SendStringAsynch(unsigned char* str);
void UART_RecvStringAsynch(unsigned char* str , volatile char** rec_done);

unsigned char UART_Receive_PerodicCheck(unsigned char *ptr);



#endif /* UART_H_ */