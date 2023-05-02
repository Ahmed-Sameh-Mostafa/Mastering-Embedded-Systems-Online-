#include "alarmMonitor.h"
#include "driver.h"

void (*ALARM_MONITOR_state) ();

alarmDuration = 600000;

void highPressureDetected()
{
	DPRINTF("high pressure detected: starting alarm in progress...............\n");
	ALARM_MONITOR_state = STATE(ALARM_MONITOR_alarmON);
}


STATE_define(ALARM_MONITOR_alarmON)
{
	alarmMonitor_state_id = alarmMonitor_alarmON;
	DPRINTF("ALARM_MONITOR_alarmON state...............\n");

	startTimer();


	ALARM_MONITOR_state = STATE(ALARM_MONITOR_waiting);
}


STATE_define(ALARM_MONITOR_alarmOFF)
{
	alarmMonitor_state_id = alarmMonitor_alarmOFF;
	DPRINTF("ALARM_MONITOR_alarmOFF state...............\n");

	stopTimer();

	ALARM_MONITOR_state = STATE(ALARM_MONITOR_alarmOFF);
}


STATE_define(ALARM_MONITOR_waiting)
{
	alarmMonitor_state_id = alarmMonitor_waiting;
	DPRINTF("ALARM_MONITOR_waiting state...............\n");


	Delay(alarmDuration);

	ALARM_MONITOR_state = STATE(ALARM_MONITOR_alarmOFF);
	ALARM_MONITOR_state();
} 