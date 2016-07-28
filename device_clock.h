#ifndef device_clock_h
#define device_clock_h

#ifndef header_h
#include <Time.h>
#include <TimeLib.h>
#endif

#include <EEPROM.h>

#define EEPROM_TIME_HEADER_ADDR  0u // Address where the time header will be stored
#define EEPROM_MAX_TIME_ACCESSES 1u // Maximum number the stored time can be used before asking for another input
#define BITS_PER_BYTE 8
#define TIME_HEADER 'T' // Header tag for serial time sync message
#define TIME_MSG_LEN 11 // Time message is the HEADER followed by Unix time_t as ten ASCII digits

const unsigned int timeAccessQttAddr = EEPROM_TIME_HEADER_ADDR + sizeof(time_t) + 1; // Address for the number of times the EEPROM was queried for the stored time

#endif
