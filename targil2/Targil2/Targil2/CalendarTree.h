#include "Node.h"
#pragma once
class CalendarTree
{
	Node *getParentForNewNode(Node *startFrom, CalendarEvent *data);

public:
	Node *root;
	CalendarTree();
	~CalendarTree();
	void printSorted();
	CalendarEvent *insert(CalendarEvent *data);
	CalendarEvent *deleteFirst();
	CalendarEvent *eventAt(time_t startTime);
	CalendarEvent *eventAfter(time_t startTime);
	int numBefore(time_t i);
};

