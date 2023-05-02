#ifndef _ALARM_MONITOR_H_
#define _ALARM_MONITOR_H_

#include "stateMachine.h"

enum {
	alarmMonitor_alarmON,
	alarmMonitor_alarmOFF,
	alarmMonitor_waiting
}alarmMonitor_state_id;

STATE_define(ALARM_MONITOR_alarmON);
STATE_define(ALARM_MONITOR_alarmOFF);
STATE_define(ALARM_MONITOR_waiting);

extern void (*ALARM_MONITOR_state) ();

#endif