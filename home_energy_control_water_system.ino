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

	Serial.print("main: checkWeekday = ");
	Serial.print(checkWeekday);
	Serial.println("");
	Serial.print("main: checkHour = ");
	Serial.print(checkHour);
	Serial.println("");
	Serial.print("main: checkMinute = ");
	Serial.print(checkMinute);
	Serial.println("");

	scheduledState = getScheduledState(checkWeekday, checkHour, checkMinute);

	Serial.print("main: scheduledState = ");
	Serial.print(scheduledState, DEC);
	Serial.print("; HIGH = ");
	Serial.print(HIGH);
	Serial.print("; LOW = ");
	Serial.print(LOW);
	Serial.println("");

	if (scheduledState == 123) {
		Serial.println("[Error] main: invalid scheduledState");
	} else {
		updatePinState(scheduledState);
	}

	while (checkMinute == minute()) {
		delay(1000);
	}
}
