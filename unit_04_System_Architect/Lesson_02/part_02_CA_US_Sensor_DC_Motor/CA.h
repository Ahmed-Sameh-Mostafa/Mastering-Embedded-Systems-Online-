#ifndef _CA_H_
#define _CA_H_

#include "stateMachine.h"
#include <stdio.h>
#include <stdlib.h>

enum {
	ca_waiting,
	ca_driving
}ca_state_id;

STATE_define(CA_waiting);
STATE_define(CA_driving);

extern void (*CA_state) ();

#endif