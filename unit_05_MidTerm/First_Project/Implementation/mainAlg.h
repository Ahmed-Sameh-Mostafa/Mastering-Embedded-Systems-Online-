#ifndef _MAIN_ALG_H_
#define _MAIN_ALG_H_

#include "stateMachine.h"

enum {
		mainAlg_highPressireDetect
}mainAlg_state_id;


STATE_define(MAIN_ALG_highPressureDetect);

extern void (*MAIN_ALG_state) ();

#endif