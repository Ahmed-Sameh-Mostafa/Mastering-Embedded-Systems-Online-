#include "CA.h"

unsigned int CA_speed = 0;
unsigned int CA_distance = 0;
unsigned int CA_threshold = 50;

void (*CA_state) ();

void US_distance_set(int d)
{
	CA_distance = d;
	(CA_distance <= CA_threshold) ? (CA_state = STATE(CA_waiting)) : (CA_state = STATE(CA_driving));
	DPRINTF("US --------distance=%d-------> CA\n", CA_distance);

}

STATE_define(CA_waiting)
{
	ca_state_id = ca_waiting;
	DPRINTF("CA_waiting state: distance= %d, speed= %d\n", CA_distance, CA_speed);

	CA_speed = 0;

	DC_motor(CA_speed);
	
}

STATE_define(CA_driving)
{
	ca_state_id = ca_driving;
	DPRINTF("CA_driving state: distance= %d, speed= %d\n", CA_distance, CA_speed);

	CA_speed = 30;

	DC_motor(CA_speed);
}



