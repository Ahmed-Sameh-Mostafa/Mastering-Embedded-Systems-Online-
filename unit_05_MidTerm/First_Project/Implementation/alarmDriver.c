#include "alarmDriver.h"
#include "driver.h"

void (*ALARM_DRIVER_state) ();


void alarmDriver_init()
{
	DPRINTF("ALARM INIT...\n");
	Set_Alarm_actuator(1);
}


void startTimer()
{
	ALARM_DRIVER_state = STATE(ALARM_DRIVER_alarmON);
	ALARM_DRIVER_state();
}


void stopTimer()
{
	ALARM_DRIVER_state = STATE(ALARM_DRIVER_alarmOFF);
	ALARM_DRIVER_state();
}


STATE_define(ALARM_DRIVER_alarmON)
{
	alarmDriver_state_id = alarmDriver_alarmON;

	Set_Alarm_actuator(0);

	ALARM_DRIVER_state = STATE(ALARM_DRIVER_waiting);
}


STATE_define(ALARM_DRIVER_alarmOFF)
{
	alarmDriver_state_id = alarmDriver_alarmOFF;

	Set_Alarm_actuator(1);

	ALARM_DRIVER_state = STATE(ALARM_DRIVER_waiting);
}


STATE_define(ALARM_DRIVER_waiting)
{
	alarmDriver_state_id = alarmDriver_waiting;


}