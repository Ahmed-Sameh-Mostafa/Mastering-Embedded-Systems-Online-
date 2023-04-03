#include "CA.h"
#include "US_Sensor.h"
#include "DC_motor.h"


void setup()
{
	US_init();
	DC_init();

	CA_state = STATE(CA_waiting);
	US_state = STATE(US_busy);
	DC_state = STATE(DC_idle);
}


void main(void)
{
	volatile int delay;
	setup();

	while(1)
	{
		US_state();
		CA_state();
		DC_state();
		for(delay = 0; delay < 1000; delay++);
	}
}