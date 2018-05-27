#include "CalendarEvent.h"
#pragma once

class Node
{
	void insertToNode1Child(Node *newChild, time_t minStartTime);
	void insertToNode2Children(Node *newChild, time_t minStartTime);
	void insertToNode3Children(Node *newChild, time_t minStartTime);
	void updateParentMin(time_t newMin);
	time_t getSmallest();
	void fixTreeAfterDeletion(Node *node);

public:
	Node *parent;
	Node *left, *mid, *right;
	time_t min2, min3;
	CalendarEvent *key;

	Node(CalendarEvent *data);
	~Node();

	Node *Find(time_t startTime, bool exactTime);
	void Insert(Node *newChild, time_t minStartTime);
	CalendarEvent *DeleteFirstLeaf();
	bool isLeaf();
	void print();
};

