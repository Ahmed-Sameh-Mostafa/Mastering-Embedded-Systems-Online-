#ifndef _PRESSURE_DRIVER_H_
#define _PRESSURE_DRIVER_H_

#include "stateMachine.h"

enum {
	pressure_reading,
	pressure_waiting
}pressureDriver_state_id;

void pressure_init();

STATE_define(PRESSURE_reading);
STATE_define(PRESSURE_waiting);

extern void (*PRESSURE_state) ();

#endif