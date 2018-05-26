#include "CalendarTree.h"
#include<iostream>


//constructor
CalendarTree::CalendarTree()
{
	root = new Node(new CalendarEvent());
	root->parent = nullptr;
	root->left = new Node(new CalendarEvent());
	root->left->parent = root;
}

//destructor
CalendarTree::~CalendarTree()
{
}

//prints the tree
void CalendarTree::printSorted() {
	//skipping "dummy root"
	root->left->print();
}

//find closest potential parent of the needed value
Node* CalendarTree::getParentForNewNode(Node *startFrom, CalendarEvent *data) {
	//make sure didnt reach to the end of tree
	if (startFrom == nullptr) {
		return nullptr;
	}

	//travelling on tree
	Node* node = startFrom;
	while (!node->isLeaf()) {
		//key is already in tree, return null
		if (node->min2 == data->getStartTime() || node->min3 == data->getStartTime())
			return nullptr;
		if (node->min2 == -1 || data->getStartTime() < node->min2)
			node = node->left;
		else if (node->min3 == -1 || data->getStartTime() < node->min3)
			node = node->mid;
		else
			node = node->right;
	}

	//check if new data overlaps with existing events
	if (node->min2 == data->getStartTime() ||
		((data->getStartTime() < node->key->getStartTime()) &&
			data->getStartTime() + data->getDuration() > node->key->getStartTime()) ||
		((data->getStartTime() > node->key->getStartTime()) &&
			node->key->getStartTime() + node->key->getDuration() > data->getStartTime())) {
		return nullptr;
	}
	
	//if key found, return parent
	return node->parent;
}

//insert new value to tree
CalendarEvent* CalendarTree::insert(CalendarEvent *data) {
	Node* newNode = new Node(data);
	newNode->min2 = data->getStartTime();

	//search for a parent node
	Node* parent = root->left;

	if (parent->left == nullptr) {
		//first insert
		newNode->parent = parent;
		parent->left = newNode;
	}
	else {
		parent = getParentForNewNode(parent, data);
		//data already in tree - no need to add
		if (parent == nullptr) {
			return nullptr;
		}

		//data isn't on tree - insert new node to its parent
		parent->Insert(newNode, data->getStartTime());
	}

	return data;
}

//calls find function on root node with exactTime=true
CalendarEvent *CalendarTree::eventAt(time_t startTime) {
	Node *node = root->Find(startTime, true);
	return node ? node->key : nullptr;
}

//calls find function on root node with exactTime=false
CalendarEvent *CalendarTree::eventAfter(time_t startTime) {
	Node *node = root->Find(startTime, false);
	return node ? node->key : nullptr;
}

//calls delete first leaf function on root node
CalendarEvent *CalendarTree::deleteFirst() {
	return root->DeleteFirstLeaf();
}

int CalendarTree::numBefore(time_t i) {
	return -1; //not implemented
}