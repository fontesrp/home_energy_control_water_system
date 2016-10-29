#include "device_clock.h"

int currentMinute() {
	return minute();
}

void currentTime(int * weekDay, int * currHour, int * currMinute) {

	time_t currentTime = now();

	*weekDay = weekday(currentTime);
    *currHour = hour(currentTime);
    *currMinute = minute(currentTime);
}

static void storeDeviceTime(time_t deviceTime) {

	unsigned int addr, bytesCount = 0;
	unsigned char value, charConverter = 0;
	time_t timeConverter = 0;

	charConverter--; // Char with all bits set to 1
	timeConverter = charConverter;

	EEPROM.write(EEPROM_TIME_HEADER_ADDR, TIME_HEADER);

	for (addr = timeAccessQttAddr - 1; addr > EEPROM_TIME_HEADER_ADDR; addr--) {

		value = (timeConverter & deviceTime) >> (bytesCount * BITS_PER_BYTE);

		EEPROM.write(addr, value);

		timeConverter = timeConverter << (sizeof(unsigned char) * BITS_PER_BYTE);
		bytesCount++;
	}

	EEPROM.write(timeAccessQttAddr, 0);
}

static time_t processSyncMessage() {

	// If time sync is available from serial port, read and return its value
	// Time message consists of header and 10 ASCII digits

	int i;
	char c;
	time_t syncTime = 0;

	while (Serial.available()) {

		syncTime = 0;
		c = Serial.read();

		if (c == TIME_HEADER) {

			for (i = 1; i < TIME_MSG_LEN && (c = Serial.read()); i++) {

				if (c >= '0' && c <= '9') {
					syncTime = 10 * syncTime + (c - '0'); // Convert digits to number
				} else {
					i = TIME_MSG_LEN;
					syncTime = 0;
				}
			}

			if (i < TIME_MSG_LEN) {
				syncTime = 0;
			}

		} else {
			syncTime = 0;
		}
	}

	return syncTime;
}

static time_t getSerialTime() {

	time_t serialTime = 0;

	if (Serial.available()) {
		serialTime = processSyncMessage();
	}

	if (serialTime == 0) {
		delay(1000);
	} else {
		storeDeviceTime(serialTime);
	}

	return serialTime;
}

static time_t readStoredTime() {

	unsigned int addr;
	unsigned char value;
	time_t storedTime = 0;

	for (addr = EEPROM_TIME_HEADER_ADDR + 1; addr < timeAccessQttAddr; addr++) {
		value = EEPROM.read(addr);
		storedTime = storedTime << (sizeof(unsigned char) * BITS_PER_BYTE);
		storedTime = storedTime | value;
	}

	return storedTime;
}

static void clearEEPROM(unsigned int firstAddr, unsigned int lastAddr) {

	unsigned int i;

	for (i = firstAddr; i <= lastAddr && i < EEPROM.length(); i++) {
		EEPROM.write(i, 0);
	}
}

static time_t getStoredTime() {

	// Time format: T1234567890. Storing it in the EEPROM in the following manner:
	// 1st byte: 'T', works as a flag for the presence of stored data;
	// Following N bytes: a time_t constant broken in single bytes from most to least significant;
	// (N + 1)th byte: number of times the EEPROM has been queried for the stored time.

	unsigned char header, accessQtt;

	header = EEPROM.read(EEPROM_TIME_HEADER_ADDR);

	if (header == TIME_HEADER) {

		accessQtt = EEPROM.read(timeAccessQttAddr);

		if (accessQtt < EEPROM_MAX_TIME_ACCESSES) {
			EEPROM.write(timeAccessQttAddr, ++accessQtt);
			return readStoredTime();
		} else {
			clearEEPROM(EEPROM_TIME_HEADER_ADDR, timeAccessQttAddr);
			return 0;
		}

	} else {
		return 0;
	}
}

void setDeviceTime() {

	time_t deviceTime;

	while (timeStatus() == timeNotSet) {

		deviceTime = getStoredTime(); // Get time stored in the EEPROM

		while (deviceTime == 0) {
			Serial.println("device_clock.ino setDeviceTime: waiting for time input");
			deviceTime = getSerialTime(); // Get time from the serial port
			Serial.print("device_clock.ino setDeviceTime: deviceTime = ");
			Serial.println(deviceTime, DEC);
		}

		setTime(deviceTime); // Sync Arduino clock
	}
}
