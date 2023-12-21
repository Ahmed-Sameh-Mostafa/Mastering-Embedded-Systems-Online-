/*
 * SPI.h
 *
 * Created: 21/12/2023 21:40:02
 *  Author: Lenovo
 */ 


#ifndef SPI_H_
#define SPI_H_

#include "AvrMemoryMap.h"

#define MASTER			1
#define SLAVE			0
#define SPI_MODE		MASTER


// PIN numbers on port b
#define SS			4
#define MOSI		5
#define MISO		6
#define SCK			7

// SPSR register and it's bits
#define SPI2X		1
#define WCOL		6
#define SPIF		7

// SPCR register and it's bits
#define SPR0		0
#define SPR1		1
#define CPHA		2
#define CPOL		3
#define MSTR		4
#define DORD		5
#define SPE			6
#define SPIE		7


void SPI_Init(void);
unsigned char SPI_SendReceive(unsigned char data);

#endif /* SPI_H_ */