/*
 * AvrMemoryMap.h
 *
 * Created: 18/12/2023 12:47:53
 *  Author: Lenovo
 */ 


#ifndef AVRMEMORYMAP_H_
#define AVRMEMORYMAP_H_

#define PORTA	(*(volatile unsigned char*) 0x3B)
#define PORTB	(*(volatile unsigned char*) 0x38)
#define PORTC	(*(volatile unsigned char*) 0x35)
#define PORTD	(*(volatile unsigned char*) 0x32)

#define DDRA			(*(volatile unsigned char*) 0x3A)
#define DDRB			(*(volatile unsigned char*) 0x37)
#define DDRC			(*(volatile unsigned char*) 0x34)
#define DDRD			(*(volatile unsigned char*) 0x31)

#define PINA			(*(volatile unsigned char*) 0x39)
#define PINB			(*(volatile unsigned char*) 0x36)
#define PINC			(*(volatile unsigned char*) 0x33)
#define PIND			(*(volatile unsigned char*) 0x30)

//base addresses
#define portA			0x3B
#define portB			0x38
#define portC			0x35
#define portD			0x32

#define output			1
#define input			0

// UART Registers
#define UDR			(*(volatile unsigned char*) 0x2C)
#define UCSRA		(*(volatile unsigned char*) 0x2B)
#define UCSRB		(*(volatile unsigned char*) 0x2A)
/*When doing a write access of this I/O location, the high bit of the value written, the USART Register Select (URSEL) bit, controls which one of the two registers that will be written. If URSEL is
zero during a write operation, the UBRRH value will be updated. If URSEL is one, the UCSRC
setting will be updated.*/
#define UCSRC		(*(volatile unsigned char*) 0x40)
#define UBRRH		(*(volatile unsigned char*) 0x40)
#define UBRRL		(*(volatile unsigned char*) 0x29)


#endif /* AVRMEMORYMAP_H_ */