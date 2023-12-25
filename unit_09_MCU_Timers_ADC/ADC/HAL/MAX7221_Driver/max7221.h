/*
 * max7221.h
 *
 * Created: 21/12/2023 23:58:07
 *  Author: Lenovo
 */ 


#ifndef MAX7221_H_
#define MAX7221_H_

#include "SPI.h"

// in order to use this driver u need to go to SPI.h and modify the SPI_MODE to MASTER


/***********************************************REGISTER ADDRESSES D8 ---> D15************************************************/
#define ADD_NO_OP				(unsigned char)0x00
#define ADD_DIGIT0				(unsigned char)0x01
#define ADD_DIGIT1				(unsigned char)0x02
#define ADD_DIGIT2				(unsigned char)0x03
#define ADD_DIGIT3				(unsigned char)0x04
#define ADD_DIGIT4				(unsigned char)0x05
#define ADD_DIGIT5				(unsigned char)0x06
#define ADD_DIGIT6				(unsigned char)0x07
#define ADD_DIGIT7				(unsigned char)0x08
#define ADD_DECODE				(unsigned char)0x09
#define ADD_INTENSITY			(unsigned char)0x0A
#define ADD_SCAN_LIMIT			(unsigned char)0x0B
#define ADD_SHUTDOWN			(unsigned char)0x0C
#define ADD_DISPLAYTEST			(unsigned char)0x0F


/***********************************************REGISTER VALUE D0 ---> D7************************************************/

// INTENSITY 
#define VALUE_INTENSITY_MAX		(unsigned char)0x0F

// DECODE
#define VALUE_DECODE_0_TO_7		(unsigned char)0xFF

// SCAN_LIMIT
#define VALUE_SCAN_LIMIT_0_TO_7 (unsigned char)0x07

// Display
#define  VALUE_DISPLAY_ON		(unsigned char)0x01



/*******************************************************FUNCTION********************************************************/	
void HAL_MAX7221_EXECUTE(unsigned char address, unsigned char value);

#endif /* MAX7221_H_ */