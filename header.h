#ifndef header_h
#define header_h

#include <Time.h>
#include <TimeLib.h>
#include <EEPROM.h>

// device_clock.ino
void setDeviceTime();
void currentTime(int * weekDay, int * hour, int * minute);
int currentMinute();

// schedule.ino
char getScheduledState(int currentWeekday, int currentHour, int currentMinute);

// pin_state.ino
void initializePins();
void updatePinState(char desiredState);

#endif
