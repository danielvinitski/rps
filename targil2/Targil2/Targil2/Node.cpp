#include "Node.h"
#include<iostream>


//constructor for Node
Node::Node(CalendarEvent *data)
{
	key = data;
	min2 = min3 = -1;
	parent = this->left = this->mid = this->right = nullptr;
}

Node::~Node()
{
}


//find node function. exactTime states whether to look for event that actually starts at startTime, or not
Node* Node::Find(time_t startTime, bool exactTime) {
	if (isLeaf()) {

		if (exactTime) {
			//check if event overlap the starttime
			if (key->getStartTime() <= startTime &&
				(key->getStartTime() + key->getDuration()) >= startTime) {
				return this;
			}
			else
				return nullptr;
		}
		else {

			//check start time of the 3 possible events in leafs
			if (parent->left->key->getStartTime() >= startTime) {
				return parent->left;
			}
			else if (parent->mid != nullptr && parent->mid->key->getStartTime() >= startTime) {
				return parent->mid;
			}
			else if (parent->right != nullptr && parent->right->key->getStartTime() >= startTime) {
				return parent->right;
			}

			//non found
			return nullptr;
		}
	}

	else { //not a leaf - keep travelling on tree

		Node* nextNode;
		if (min3 != -1 && startTime >= min3) {
			nextNode = right;
		}
		else if (min2 != -1 && startTime >= min2) {
			nextNode = mid;
		}
		else {
			nextNode = left;
		}

		return nextNode ? nextNode->Find(startTime, exactTime) : nullptr;
	}
}

//Insert Node under current node
void Node::Insert(Node *newNode, time_t minStartTime) {
	//go to the right function by number of children
	if (right == nullptr) {
		if (mid == nullptr) {
			//insert to a node with 1 child
			insertToNode1Child(newNode, minStartTime);
		}
		else {
			//insert to a node with 2 children
			insertToNode2Children(newNode, minStartTime);
		}
	}
	else {
		//insert to a node with 3 children
		insertToNode3Children(newNode, minStartTime);
	}
}

//insert node when only 1 child
void Node::insertToNode1Child(Node *newChild, time_t minStartTime) {
	newChild->parent = this;

	if (newChild->min2 < left->min2) {
		//insert new child to left
		mid = left;
		left = newChild;
		min2 = mid->getSmallest();
	}
	else {
		//insert new child to mid
		mid = newChild;
		min2 = newChild->min2;
	}
}

//insert node when 2 children
void Node::insertToNode2Children(Node *newChild, time_t minStartTime) {
	time_t newKey = newChild->min2;
	newChild->parent = this;

	if (newKey < left->min2) {
		//insert new child to left
		right = mid;
		mid = left;
		left = newChild;
		min3 = min2;
		min2 = mid->getSmallest();

		updateParentMin(minStartTime);
	}
	else if (newKey < mid->min2) {
		//insert new child to mid
		right = mid;
		mid = newChild;
		min3 = min2;
		min2 = minStartTime;
	}
	else {
		//insert new child to right
		right = newChild;
		min3 = minStartTime;
	}
}

//insert node when 3 children
void Node::insertToNode3Children(Node *newChild, time_t minStartTime) {
	time_t newKey = newChild->min2;

	//define a split node, to make room for the new node
	Node* splitNode = new Node(new CalendarEvent());
	time_t splitSmallest = -1;
	splitNode->parent = parent;

	if (newKey < left->min2 || newKey < mid->min2) {
		//insert newChild in current node
		splitSmallest = min2;
		splitNode->left = mid;
		splitNode->mid = right;
		splitNode->min2 = min3;

		//update parents
		mid->parent = splitNode;
		right->parent = splitNode;
		newChild->parent = this;

		if (newKey < left->min2) {
			//insert newChild to left
			mid = left;
			left = newChild;

			min2 = mid->getSmallest();
			updateParentMin(minStartTime);
		}
		else {
			//insert newChild to mid
			mid = newChild;
			min2 = minStartTime;
		}
	}
	else {
		//insert newChild in split node
		right->parent = splitNode;
		newChild->parent = splitNode;

		if (newKey < right->min2) {
			//insert newChild to left
			splitSmallest = minStartTime;
			splitNode->left = newChild;
			splitNode->mid = right;
			splitNode->min2 = min3;
		}
		else {
			//insert newChild to mid
			splitSmallest = min3;
			splitNode->left = right;
			splitNode->mid = newChild;
			splitNode->min2 = minStartTime;
		}
	}

	right = nullptr;
	min3 = -1;

	if (parent->parent == nullptr) {
		//create new root
		Node *newRoot = new Node(new CalendarEvent());

		parent->left = newRoot;
		newRoot->parent = parent;
		newRoot->left = this;
		parent = newRoot;
	}

	parent->Insert(splitNode, splitSmallest);
}

//update parents with new min time
void Node::updateParentMin(time_t newMin) {
	if (parent == nullptr) return;

	// Update the parent nodes
	if (parent->left == this) {
		if (parent->parent != nullptr) {
			parent->updateParentMin(newMin);
		}
	}
	else if (parent->mid == this) {
		parent->min2 = newMin;
	}
	else {
		parent->min3 = newMin;
	}
}

//get the smallest min value of current sub tree
time_t Node::getSmallest() {
	//travel to the leftest leaf
	Node *node = this;
	while (!node->isLeaf()) node = node->left;
	return node->key->getStartTime();
}

//get number of children of current node
int Node::numChildren() {
	int c = 0;
	if (right != nullptr) c++;
	if (mid != nullptr) c++;
	if (left != nullptr) c++;
	return c;
}

//check if current node is a leaf or not
bool Node::isLeaf() {
	return left == nullptr;
}

//print current node
void Node::print() {
	if (isLeaf()) {
		//print
		key->print();
	}
	else {
		//print sorted, left to right
		if (left != nullptr) left->print();
		if (mid != nullptr) mid->print();
		if (right != nullptr) right->print();
	}
}

//delete first leaf under current sub tree
CalendarEvent *Node::DeleteFirstLeaf() {
	
	//travel to leftest leaf
	Node *node = this;
	while (!node->isLeaf()) {
		node = node->left;
	}
	
	//update parents after deletion
	fixTreeAfterDeletion(node->parent);
	
	//keep original value to return
	CalendarEvent *event = node->key;

	//clean memory
	delete node;

	return event;
}

//update values from curren node to root when deleting a node
void Node::fixTreeAfterDeletion(Node *node) const {
	//3 children before deletion
	if (node->right != nullptr) {
		//moving each node step to the right
		node->left = node->mid;
		node->mid = node->right;
		node->right = nullptr;

		//update min values
		node->min2 = node->mid->getSmallest();
		node->min3 = -1;
	}
	//2 children before deletion
	else if (node->mid != nullptr) {
		//move to the right
		node->left = node->mid;
		
		//update min values
		node->mid = nullptr;
		node->min2 = -1;
	}
	//1 child before deletion
	else {
		//delete only if not tree root
		if (node->parent != nullptr) {
			node->left = nullptr;
			fixTreeAfterDeletion(node->parent);
		}
	}
}