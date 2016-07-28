#include "pin_state.h"

void updatePinState(char desiredState) {

	int i;

	Serial.print("pin_state.ino updatePinState: currentPinState = ");
	Serial.print(currentPinState, DEC);
	Serial.println("");
	Serial.print("pin_state.ino updatePinState: desiredState = ");
	Serial.print(desiredState, DEC);
	Serial.println("");

	if (desiredState != currentPinState) {

		for (i = 0; i < BIPHASIC_CIRCUITS_QTT; i++) {
			digitalWrite(biphasicCircuits[i].pin0, desiredState);
			digitalWrite(biphasicCircuits[i].pin1, desiredState);
		}

		for (i = 0; i < MONOPHASIC_CIRCUITS_QTT; i++) {
			digitalWrite(monophasicCircuits[i].pin, desiredState);
		}

		currentPinState = desiredState;
	}
}

void setCircuits() {

	biphasicCircuits[0].pin0 = 2;
	biphasicCircuits[0].pin1 = 3;

	biphasicCircuits[1].pin0 = 4;
	biphasicCircuits[1].pin1 = 5;

	biphasicCircuits[2].pin0 = 6;
	biphasicCircuits[2].pin1 = 7;

	monophasicCircuits[0].pin = 8;

	monophasicCircuits[1].pin = 9;
}

void initializePins() {

	int i;

	if (!circuitsSet) {
		setCircuits();
		circuitsSet = 1;
	}

	currentPinState = LOW;

	for (i = 0; i < BIPHASIC_CIRCUITS_QTT; i++) {
		pinMode(biphasicCircuits[i].pin0, OUTPUT);
		pinMode(biphasicCircuits[i].pin1, OUTPUT);
		digitalWrite(biphasicCircuits[i].pin0, currentPinState);
		digitalWrite(biphasicCircuits[i].pin1, currentPinState);
	}

	for (i = 0; i < MONOPHASIC_CIRCUITS_QTT; i++) {
		pinMode(monophasicCircuits[i].pin, OUTPUT);
		digitalWrite(monophasicCircuits[i].pin, currentPinState);
	}
}
