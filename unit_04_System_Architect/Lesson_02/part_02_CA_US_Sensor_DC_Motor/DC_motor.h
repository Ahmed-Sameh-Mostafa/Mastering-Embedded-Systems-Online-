#ifndef _DC_MOTOR_H_
#define _DC_MOTOR_H_

#include "stateMachine.h"

enum {
	dc_idle,
	dc_busy
}DC_state_id;

void DC_init();

STATE_define(DC_idle);
STATE_define(DC_busy);

extern void (*DC_state) ();


#endif