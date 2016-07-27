#ifndef header_h
#define header_h

#include <Time.h>
#include <TimeLib.h>

void setDeviceTime(); // device_clock.ino
char getScheduledState(int currentWeekday, int currentHour, int currentMinute); // schedule.ino
void initializePins(); // pin_state.ino
void updatePinState(char desiredState); // pin_state.ino

#endif
