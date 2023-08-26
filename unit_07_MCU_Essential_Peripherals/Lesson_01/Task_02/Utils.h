/*
 * Utils.h
 *
 * Created: 26/08/2023 17:03:16
 *  Author: Lenovo
 */ 


#ifndef UTILS_H_
#define UTILS_H_

#define SetBit(reg, bit) (reg |= (1<<bit))
#define ClearBit(reg, bit) (reg &= ~(1<<bit))
#define ReadBit(reg, bit) ((reg >> bit) & 1)
#define ToggleBit(reg, bit) (reg ^= (1<<bit)) 

#endif /* UTILS_H_ */