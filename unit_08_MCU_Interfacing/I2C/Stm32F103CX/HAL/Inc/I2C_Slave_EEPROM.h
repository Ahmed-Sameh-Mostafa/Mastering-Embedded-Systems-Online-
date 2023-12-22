/*
 * I2C_Slave_EEPROM.h
 *
 *  Created on: 27 Nov 2023
 *      Author: Lenovo
 */

#ifndef INC_I2C_SLAVE_EEPROM_H_
#define INC_I2C_SLAVE_EEPROM_H_

#include "Stm32_F103C6_I2C_driver.h"

#define EEPROM_Slave_address		0x2A

void eeprom_init(void);

unsigned char eeprom_write_Nbytes(unsigned int Memory_address, unsigned char* bytes, uint8_t Data_Length);

unsigned char eeprom_read_byte(unsigned int address, uint8_t* dataOut, uint8_t dataLen);

#endif /* INC_I2C_SLAVE_EEPROM_H_ */
