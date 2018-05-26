#include "time.h"
#include <string>
using namespace std;

#pragma once

class CalendarEvent
{
	time_t startTime; // time_t is defined in the header file <ctime>
	time_t duration; // duration of the event, in seconds
	string description; // should not contain special characters or newline
public:
	// constructor, destructor, other methods as needed
	CalendarEvent(time_t startTime, time_t duration, string desc);
	CalendarEvent() = default;
	~CalendarEvent();
	void print(); // "print" the event to cout
	time_t getStartTime();
	time_t getDuration();
};