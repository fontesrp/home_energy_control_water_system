#include "header.h"

void setup() {

	Serial.begin(9600);

	initializePins();

	while (timeStatus() == timeNotSet) {
		setDeviceTime();
	}
}

void loop() {

	time_t checkTime;
	int checkWeekday, checkHour, checkMinute;
	char scheduledState;

	checkTime = now();

	checkWeekday = weekday(checkTime);
	checkHour = hour(checkTime);
	checkMinute = minute(checkTime);

	scheduledState = getScheduledState(checkWeekday, checkHour, checkMinute);

	if (scheduledState == -1) {
		Serial.println("Error: invalid scheduledState");
	} else {
		updatePinState(scheduledState);
	}

	while (checkMinute == minute()) {
		delay(1000);
	}
}
