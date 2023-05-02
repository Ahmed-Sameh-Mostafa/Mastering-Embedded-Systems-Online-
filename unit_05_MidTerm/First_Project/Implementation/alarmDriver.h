#ifndef _ALARM_DRIVER_H_
#define _ALARM_DRIVER_H_

#include "stateMachine.h"

enum {
	alarmDriver_alarmON,
	alarmDriver_alarmOFF,
	alarmDriver_waiting
}alarmDriver_state_id;

void alarmDriver_init();

STATE_define(ALARM_DRIVER_alarmON);
STATE_define(ALARM_DRIVER_alarmOFF);
STATE_define(ALARM_DRIVER_waiting);

extern void (*ALARM_DRIVER_state) ();

#endif