#include "pressureDriver.h"
#include "driver.h"
#include "platform_Types.h"
#include "alarmMonitor.h"
#include "mainAlg.h"
#include "alarmDriver.h"


void setup()
{
	GPIO_INITIALIZATION();

	pressure_init();
	alarmDriver_init();


	PRESSURE_state = STATE(PRESSURE_reading);
	MAIN_ALG_state = STATE(MAIN_ALG_highPressureDetect);
	ALARM_MONITOR_state = STATE(ALARM_MONITOR_alarmOFF);
	ALARM_DRIVER_state = STATE(ALARM_DRIVER_waiting);

}

int main ()
{
	setup();

	while (1)
	{
		//Implement your Design
		PRESSURE_state();
		MAIN_ALG_state();
		ALARM_MONITOR_state();
		ALARM_DRIVER_state(); 
	}

}
