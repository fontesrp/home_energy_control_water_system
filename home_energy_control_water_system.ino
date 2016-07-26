#include "header.h"

void setup() {
	Serial.begin(9600);

}

void loop() {

	if (Serial.available()) {
		processSyncMessage();
	}

	if (timeStatus() == timeNotSet) {
		Serial.println("waiting for sync message");
	} else {
		digitalClockDisplay();
	}

	delay(1000);
}
