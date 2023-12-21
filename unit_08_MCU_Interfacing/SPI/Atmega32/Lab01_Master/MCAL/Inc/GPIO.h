/*
 * GPIO.h
 *
 * Created: 18/12/2023 13:28:02
 *  Author: Lenovo
 */ 


#ifndef GPIO_H_
#define GPIO_H_


void Port_Direction(unsigned char base, unsigned char state); // base is register port

void Pin_Direction(unsigned char base, unsigned char pin,unsigned char state); // base is register port


#endif /* GPIO_H_ */