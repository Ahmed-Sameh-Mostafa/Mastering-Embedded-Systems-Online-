#include "CA.h"

unsigned int speed = 0;
unsigned int distance = 0;
unsigned int threshold = 50;

void (*CA_state) ();

int generate_random(int l, int r, int count);

STATE_define(CA_waiting)
{
	state_id = waiting;
	speed = 0;
	distance = generate_random(45, 55, 1);

	(distance <= threshold) ? (CA_state = STATE(CA_waiting)) : (CA_state = STATE(CA_driving));
	DPRINTF("waiting state: distance= %d, speed= %d\n", distance, speed);
}

STATE_define(CA_driving)
{
	state_id = driving;
	speed = 30;
	distance = generate_random(45, 55, 1);

	(distance <= threshold) ? (CA_state = STATE(CA_waiting)) : (CA_state = STATE(CA_driving));
	DPRINTF("driving state: distance= %d, speed= %d\n", distance, speed);
}


int generate_random(int l, int r, int count)
{
	int i, rand_num;
	for(i = 0; i < count; i++)
		rand_num = (rand() % (r-l+1)) + l;
	return rand_num;
}


