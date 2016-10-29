#include "schedule.h"

static int treatIndex(int index) {

	if (index < 0) {
		index = SCHEDULE_DATES_QTT - 1;
	} else if (index >= SCHEDULE_DATES_QTT) {
		index = 0;
	}

	return index;
}

static int findTimeIndex(int searchWeekday, int searchHour, int searchMinute, int index) {

	if (searchWeekday < scheduleDates[index].weekday) {
		index--;
	} else if (searchWeekday > scheduleDates[index].weekday) {
		index = treatIndex(++index);
		index = findTimeIndex(searchWeekday, searchHour, searchMinute, index);
	} else if (searchHour < scheduleDates[index].hour) {
		index--;
	} else if (searchHour > scheduleDates[index].hour) {
		index = treatIndex(++index);
		index = findTimeIndex(searchWeekday, searchHour, searchMinute, index);
	} else if (searchMinute < scheduleDates[index].minute) {
		index--;
	} else if (searchMinute > scheduleDates[index].minute) {
		index = treatIndex(++index);
		index = findTimeIndex(searchWeekday, searchHour, searchMinute, index);
	}

	return treatIndex(index);
}

static int findIndex(int searchWeekday, int searchHour, int searchMinute) {

	int i, index = 0;

	// This loop will return the first schedule for the searched weekday, which should have state CIRCUIT_OFF
	for (i = 0; i < SCHEDULE_DATES_QTT; i++) {

		if (scheduleDates[i].weekday == searchWeekday) {
			index = i;
			i = SCHEDULE_DATES_QTT;
		}
	}

	if (i == SCHEDULE_DATES_QTT) {
		return -1;
	} else {
		return findTimeIndex(searchWeekday, searchHour, searchMinute, index);
	}
}

static void setScheduleDates() {

	// Must be organized in ascending order from Sunday 00:00, always with one CIRCUIT_ON for every CIRCUIT_OFF in the same day

	scheduleDates[0].weekday = 1; // Sunday 01:00 OFF
	scheduleDates[0].hour = 1;
	scheduleDates[0].minute = 0;
	scheduleDates[0].state = CIRCUIT_OFF;

	scheduleDates[1].weekday = 1; // Sunday 05:00 ON
	scheduleDates[1].hour = 5;
	scheduleDates[1].minute = 0;
	scheduleDates[1].state = CIRCUIT_ON;

	scheduleDates[2].weekday = 2; // Monday 01:00 OFF
	scheduleDates[2].hour = 1;
	scheduleDates[2].minute = 0;
	scheduleDates[2].state = CIRCUIT_OFF;

	scheduleDates[3].weekday = 2; // Monday 04:00 ON
	scheduleDates[3].hour = 4;
	scheduleDates[3].minute = 0;
	scheduleDates[3].state = CIRCUIT_ON;

	scheduleDates[4].weekday = 3; // Tuesday 01:00 OFF
	scheduleDates[4].hour = 1;
	scheduleDates[4].minute = 0;
	scheduleDates[4].state = CIRCUIT_OFF;

	scheduleDates[5].weekday = 3; // Tuesday 04:00 ON
	scheduleDates[5].hour = 4;
	scheduleDates[5].minute = 0;
	scheduleDates[5].state = CIRCUIT_ON;

	scheduleDates[6].weekday = 4; // Wednesday 01:00 OFF
	scheduleDates[6].hour = 1;
	scheduleDates[6].minute = 0;
	scheduleDates[6].state = CIRCUIT_OFF;

	scheduleDates[7].weekday = 4; // Wednesday 04:00 ON
	scheduleDates[7].hour = 4;
	scheduleDates[7].minute = 0;
	scheduleDates[7].state = CIRCUIT_ON;

	scheduleDates[8].weekday = 5; // Thursday 01:00 OFF
	scheduleDates[8].hour = 1;
	scheduleDates[8].minute = 0;
	scheduleDates[8].state = CIRCUIT_OFF;

	scheduleDates[9].weekday = 5; // Thursday 04:00 ON
	scheduleDates[9].hour = 4;
	scheduleDates[9].minute = 0;
	scheduleDates[9].state = CIRCUIT_ON;

	scheduleDates[10].weekday = 6; // Friday 01:00 OFF
	scheduleDates[10].hour = 1;
	scheduleDates[10].minute = 0;
	scheduleDates[10].state = CIRCUIT_OFF;

	scheduleDates[11].weekday = 6; // Friday 04:00 ON
	scheduleDates[11].hour = 4;
	scheduleDates[11].minute = 0;
	scheduleDates[11].state = CIRCUIT_ON;

	scheduleDates[12].weekday = 7; // Saturday 01:00 OFF
	scheduleDates[12].hour = 1;
	scheduleDates[12].minute = 0;
	scheduleDates[12].state = CIRCUIT_OFF;

	scheduleDates[13].weekday = 7; // Saturday 05:00 ON
	scheduleDates[13].hour = 5;
	scheduleDates[13].minute = 0;
	scheduleDates[13].state = CIRCUIT_ON;
}

char getScheduledState(int currentWeekday, int currentHour, int currentMinute) {

	int scheduleIndex;

	if (!scheduleSet) {
		setScheduleDates();
		scheduleSet = 1;
	}

	scheduleIndex = findIndex(currentWeekday, currentHour, currentMinute);

	if (scheduleIndex == -1) {
		return 123;
	} else {
		return scheduleDates[scheduleIndex].state;
	}
}
