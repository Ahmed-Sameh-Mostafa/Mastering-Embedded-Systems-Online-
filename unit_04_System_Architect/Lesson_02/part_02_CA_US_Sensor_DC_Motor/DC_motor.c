#include "DC_motor.h"


unsigned int DC_speed = 0;

void (*DC_state) ();

void DC_init()
{
	DPRINTF("DC_init\n");
}

void DC_motor(int s)
{
	DC_speed = s;
	DC_state = STATE(DC_busy);
	printf("CA ------speed=%d------> DC,    DC_motor()\n", DC_speed);
}

STATE_define(DC_idle)
{
	DC_state_id = dc_idle;


	DPRINTF("DC_idle state: speed= %d\n\n", DC_speed);
}

STATE_define(DC_busy)
{
	DC_state_id = dc_busy;
	DC_state = STATE(DC_idle);
	

	DPRINTF("DC_busy state: speed= %d\n\n", DC_speed);
}


