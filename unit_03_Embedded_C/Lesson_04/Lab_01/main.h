// created by Ahmed Sameh in Mastering embedded systems diploma
#ifndef MAIN_H
#define MAIN_H
#include <platform_Types.h>


#define SYSTCK_RCGC2_R 			(*((volatile uint32 *)0x400FE108))
#define GPIO_PORTF_DATA_R 		(*((volatile uint32 *)0x400253FC))
#define GPIO_PORTF_DIR_R 		(*((volatile uint32 *)0x40025400))
#define GPIO_PORTF_DEN_R 		(*((volatile uint32 *)0x4002551C))

#endif