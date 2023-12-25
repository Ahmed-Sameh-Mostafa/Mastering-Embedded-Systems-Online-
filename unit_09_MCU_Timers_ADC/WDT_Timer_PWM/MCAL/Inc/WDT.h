/*
 * WDT.h
 *
 * Created: 24/12/2023 13:15:19
 *  Author: Lenovo
 */ 


#ifndef WDT_H_
#define WDT_H_

#include <avr/interrupt.h>
#include <avr/io.h>
#include "Utils.h"

void WDT_ON();

void WDT_OFF();


#endif /* WDT_H_ */