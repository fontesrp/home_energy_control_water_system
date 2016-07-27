#ifndef pin_state_h
#define pin_state_h

#define BIPHASIC_CIRCUITS_QTT 3
#define MONOPHASIC_CIRCUITS_QTT 2

struct biphasic {
	char pin0, pin1;
} biphasicCircuits[BIPHASIC_CIRCUITS_QTT];

struct monophasic {
	char pin;
} monophasicCircuits[MONOPHASIC_CIRCUITS_QTT];

char currentPinState;
char circuitsSet = 0;

#endif
