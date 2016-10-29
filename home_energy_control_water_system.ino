#include "header.h"

void setup() {
	Serial.begin(9600);
	initializePins();
	setDeviceTime();
}

void loop() {

	int checkWeekday, checkHour, checkMinute;
	char scheduledState;

	currentTime(&checkWeekday, &checkHour, &checkMinute);

	Serial.print("main: weekday = ");
	Serial.println(checkWeekday, DEC);
	Serial.print("main: hour = ");
	Serial.println(checkHour, DEC);
	Serial.print("main: minute = ");
	Serial.println(checkMinute, DEC);

	scheduledState = getScheduledState(checkWeekday, checkHour, checkMinute);

	Serial.print("main: scheduledState = ");
	Serial.println(scheduledState, DEC);

	if (scheduledState == 123) {
		Serial.println("[Error] main: invalid scheduledState");
	} else {
		updatePinState(scheduledState);
	}

	while (checkMinute == currentMinute()) {
		delay(1000);
	}
}
