/*
 * Servo_Motor.h
 *
 *  Created on: Nov 12, 2021
 *      Author:  Mostafa Mahmoud Elshiekh
 */



#ifndef SERVO_MOTOR_SERVO_MOTOR_H_
#define SERVO_MOTOR_SERVO_MOTOR_H_

#include "STM32_F103C6.h"
#include "Stm32_F103C6_gpio_driver.h"
#include "Timer.h"

#define UP   1
#define Down 2


void Servo1_Entry_Gate_Init(void);
void Servo1_Entry_Gate(uint8_t Direction);

void Servo2_Exit_Gate_Init(void);
void Servo2_Exit_Gate(uint8_t Direction);




#endif /* SERVO_MOTOR_SERVO_MOTOR_H_ */
