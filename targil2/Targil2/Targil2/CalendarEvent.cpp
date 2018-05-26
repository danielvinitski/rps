#include "CalendarEvent.h"
#include <iostream>
using namespace std;

CalendarEvent::CalendarEvent(time_t startTime, time_t duration, std::string desc) {
	this->startTime = startTime;
	this->duration = duration;
	this->description = desc;
}

void CalendarEvent::print()
{
	cout << this->startTime << " " << this->duration << this->description << "\n";
}

CalendarEvent::~CalendarEvent()
{
}

//getters
time_t CalendarEvent::getStartTime() {
	return this->startTime;
}

time_t CalendarEvent::getDuration() {
	return this->duration;
}