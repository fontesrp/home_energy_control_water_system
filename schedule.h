#ifndef schedule_h
#define schedule_h

#define CIRCUIT_ON  LOW  // Pin in low state  -> relay leaves the circuit ON as default
#define CIRCUIT_OFF HIGH // Pin in high state -> activate relay to open the circuit
#define SCHEDULE_DATES_QTT 14 // One schedule to turn off and one to turn on for each day of the week

struct schedule {
	int weekday; // 1 = Sunday, ...
	int hour;    // 0..23
	int minute;  // 0..59
	char state;  // ON/OFF
} scheduleDates[SCHEDULE_DATES_QTT];

char scheduleSet = 0;

#endif
