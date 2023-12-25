/*
 * Utils.h
 *
 * Created: 24/12/2023 13:09:51
 *  Author: Lenovo
 */ 


#ifndef UTILS_H_
#define UTILS_H_


/******************************************************************************
*                               FUNCTION-LIKE MACROS                          *
*******************************************************************************/
#define CLEAR_BIT(reg, bit)		(reg &= ~(1<<bit))
#define SET_BIT(reg, bit)		(reg |= (1<<bit))
#define TOGGLE_BIT(reg, bit)	(reg ^= (1<<bit))
#define READ_BIT(reg, bit)		((reg >> bit) & 1)



#endif /* UTILS_H_ */