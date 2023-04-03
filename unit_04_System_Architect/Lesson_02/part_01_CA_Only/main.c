#include "CA.h"



void setup()
{
	CA_state = STATE(CA_waiting);
}


void main(void)
{
	volatile int delay;
	setup();

	while(1)
	{

		CA_state();
		for(delay = 0; delay < 1000; delay++);
	}
}