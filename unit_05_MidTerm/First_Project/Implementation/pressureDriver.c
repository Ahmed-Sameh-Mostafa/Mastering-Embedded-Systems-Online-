#include "pressureDriver.h"
#include "driver.h"
#include "platform_Types.h"

void (*PRESSURE_state) ();
static uint32 pVal = 0;

void pressure_init()
{
	DPRINTF("PRESSURE INIT...\n");
}

STATE_define(PRESSURE_reading)
{
	pressureDriver_state_id = pressure_reading;

	//reading from sensor
	pVal = getPressureVal();

	DPRINTF("pressure_reading state, pVal = %d\n",pVal);

	//sending the pressure signal
	readPressureValue(pVal);

	//next state
	PRESSURE_state = STATE(PRESSURE_waiting);

}


STATE_define(PRESSURE_waiting)
{
	pressureDriver_state_id = pressure_waiting;

	//Delay
	Delay(200000);

	//next state
	PRESSURE_state = STATE(PRESSURE_reading);
}
