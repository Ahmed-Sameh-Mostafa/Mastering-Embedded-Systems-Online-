#ifndef _STATEMAHCINE_H_
#define _STATEMAHCINE_H_

#define STATE_define(_stateFunc_)	void ST_##_stateFunc_(void)
#define STATE(_stateFunc_)	ST_##_stateFunc_

#define DPRINTF(...)	{/*fflush(stdin);\
						fflush(stdout);\
						printf(__VA_ARGS__);\
						fflush(stdin);\
						fflush(stdout);*/}

#include <stdio.h>
#include <stdlib.h>
#include <platform_Types.h>

//states connection
void readPressureValue(int pValue);
void highPressureDetected();
void startTimer();
void stopTimer();

#endif