#ifndef _US_SENSOR_H_
#define _US_SENSOR_H_

#include "stateMachine.h"

enum {
	us_busy
}US_state_id;

void US_init();

STATE_define(US_busy);

extern void (*US_state) ();


#endif