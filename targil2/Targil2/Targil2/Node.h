#include "calendarEvent.h"
#pragma once

class Node
{
	void insertToNode1Child(Node *newChild);
	void insertToNode2Children(Node *newChild);
	void insertToNode3Children(Node *newChild);
	void updateParentMin(int data);
	int getSmallest();
	int numChildren();

public:
	Node *parent;
	Node *left, *mid, *right;
	int min2, min3;
	int key;

	Node(int data);
	~Node();
	Node *Find(int data);
	void Insert(Node *newChild);
	void Delete(int data);
	bool isLeaf();
	void print();
};

