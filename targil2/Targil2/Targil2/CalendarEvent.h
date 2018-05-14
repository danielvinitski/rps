#include "time.h"
#include <string>
using namespace std;

class CalendarEvent
{
	time_t startTime; // time_t is defined in the header file <ctime>
	time_t duration; // duration of the event, in seconds
	string description; // should not contain special characters or newline
public:
	// constructor, destructor, other methods as needed
	CalendarEvent();
	~CalendarEvent();
	void print(); // "print" the event to cout
};