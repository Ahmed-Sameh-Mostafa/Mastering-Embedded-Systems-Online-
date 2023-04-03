#include "US_Sensor.h"


unsigned int US_distance = 0;

void (*US_state) ();

int US_generate_random(int l, int r, int count);


void US_init()
{
	DPRINTF("US_init\n");
}

STATE_define(US_busy)
{
	US_state_id = us_busy;

	US_distance = US_generate_random(45, 55, 1);

	// (distance <= threshold) ? (CA_state = STATE(CA_waiting)) : (CA_state = STATE(CA_driving));
	DPRINTF("US_busy state: distance= %d\n", US_distance);

	US_distance_set(US_distance);
	US_state = STATE(US_busy);
}



int US_generate_random(int l, int r, int count)
{
	int i, rand_num;
	for(i = 0; i < count; i++)
		rand_num = (rand() % (r-l+1)) + l;
	return rand_num;
}


