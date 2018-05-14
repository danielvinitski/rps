#include "Node.h"
#pragma once
class CalendarTree
{
	Node *getParentForNewNode(Node *startFrom, int data);

public:
	Node *root;
	CalendarTree();
	~CalendarTree();
	void printSorted();
	void Insert(int data);
	void Delete(int data);

	void print(Node *node, int tabs = 0);
};

