#include "CalendarTree.h"
#include<iostream>


CalendarTree::CalendarTree()
{
	root = new Node(-1);
	root->parent = nullptr;
	root->left = new Node(-1);
	root->left->parent = root;
}


CalendarTree::~CalendarTree()
{
}

void CalendarTree::printSorted() {
	root->print();
}


Node* CalendarTree::getParentForNewNode(Node *startFrom, int data) {
	//make sure didnt reach to the end of tree
	if (startFrom == nullptr) {
		return nullptr;
	}

	//travelling on tree
	Node* node = startFrom;
	while (!node->isLeaf()) {
		if (node->min2 == data || node->min3 == data)
			return nullptr;
		if (node->min2 == -1 || data < node->min2)
			node = node->left;
		else if (node->min3 == -1 || data < node->min3)
			node = node->mid;
		else
			node = node->right;
	}

	//data already in tree
	if (node->key == data) {
		return nullptr;
	}
	else {
		return node->parent;
	}
}

void CalendarTree::Insert(int data) {
	Node* newNode = new Node(data);

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
			return;
		}

		//data isn't on tree - insert new node
		parent->Insert(newNode);
	}
}


void CalendarTree::Delete(int data) {
	Node *parent = getParentForNewNode(root->left, data);
	parent->Delete(data);
}

//debug
void CalendarTree::print(Node *node, int tabs) {
	// Recursively print the subtree starting from the given node

	for (int i = 0; i < tabs; ++i) {
		cout << "\t";
	}

	if (node == nullptr) {
		cout << "`--> NULL" << endl;
		return;
	}

	cout << "`--> "
		<< ": ( " << node->min2 << ", " << node->min3 << ")" << endl;

	if (!node->isLeaf()) {
		++tabs;
		print(node->left, tabs);
		print(node->mid, tabs);
		print(node->right, tabs);
	}
}