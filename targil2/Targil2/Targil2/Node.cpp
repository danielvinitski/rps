#include "Node.h"
#include<iostream>


Node::Node(int data)
{
	key = min2 = data;
	min3 = -1;
}


Node::~Node()
{
}


Node* Node::Find(int data) {
	if (isLeaf()) {
		if (key == data) {
			return this;
		}
		else {
			return nullptr;
		}
	}

	else { //not a leaf - keep travelling on tree

		Node* nextNode;
		if (right != nullptr && data >= min3) {
			nextNode = right;
		}
		else if (data >= min2) {
			nextNode = mid;
		}
		else {
			nextNode = left;
		}

		return nextNode->Find(data);
	}
}


void Node::Insert(Node *newNode) {
	if (right == nullptr) {
		if (mid == nullptr) {
			//insert to a node with 1 child
			insertToNode1Child(newNode);
		}
		else {
			//insert to a node with 2 children
			insertToNode2Children(newNode);
		}
	}
	else {
		//insert to a node with 3 children
		insertToNode3Children(newNode);
	}
}

void Node::insertToNode1Child(Node *newChild) {
	int newKey = newChild->getSmallest();
	newChild->parent = this;

	if (newKey < left->getSmallest()) {
		//insert new child to left
		mid = left;
		left = newChild;
		min2 = mid->key;//smallaest
	}
	else {
		//insert new child to mid
		mid = newChild;
		min2 = newKey;
	}
}

void Node::insertToNode2Children(Node *newChild) {
	int newKey = newChild->key;
	newChild->parent = this;

	if (newKey < left->key) {
		//insert new child to left
		right = mid;
		mid = left;
		left = newChild;
		min2 = mid->key;//smallaest
		min3 = right->key;

		updateParentMin(newKey);
	}
	else if (newKey < mid->key) {
		//insert new child to mid
		right = mid;
		mid = newChild;
		min2 = newKey;
		min3 = right->key;
	}
	else {
		//insert new child to right
		right = newChild;
		min3 = newKey;
	}
}

void Node::insertToNode3Children(Node *newChild) {
	int newKey = newChild->key;

	Node* splitNode = new Node(-1);
	splitNode->parent = parent;

	if (newKey < left->key || newKey < mid->key) {
		//insert newChild in current node
		splitNode->left = mid;
		splitNode->mid = right;
		splitNode->min2 = right->key;

		//update parents
		mid->parent = splitNode;
		right->parent = splitNode;
		newChild->parent = this;

		if (newKey < left->key) {
			//insert newChild to left
			mid = left;
			left = newChild;

			min2 = left->key; //smallaest
			updateParentMin(newKey);
		}
		else {
			//insert newChild to mid
			mid = newChild;
			min2 = newKey;
		}
	}
	else {
		//insert newChild in split node
		right->parent = splitNode;
		newChild->parent = splitNode;

		if (newKey < right->min2) {
			//insert newChild to left
			splitNode->left = newChild;
			splitNode->mid = right;
			splitNode->min2 = min3;
		}
		else {
			//insert newChild to mid
			splitNode->left = right;
			splitNode->mid = newChild;
			splitNode->min2 = newKey;
		}
	}

	right = nullptr;
	min3 = -1;

	if (parent->parent == nullptr) {
		//create new root
		Node *newRoot = new Node(-1);

		parent->left = newRoot;
		newRoot->parent = parent;
		newRoot->left = this;
		parent = newRoot;

		/*
		//min2 = newNode;
		newRoot->parent = nullptr;
		newRoot->left = this;
		newRoot->mid = splitNode;
		splitNode->parent = newRoot;
		parent = newRoot;*/
	}

	parent->Insert(splitNode);
}

void Node::Delete(int data) {
	//remove leaf
	if (right->key == data) {
		right = nullptr;
		min3 = -1;
	}
	else if (mid->key == data) {
		mid = nullptr;
		min3 = -1;
	}
	else if (left->key == data) {
		left = nullptr;
	}

	//now rearrange tree
	if (numChildren() == 2) {
		if (right==nullptr) {
			return;
		}
		else if (mid == nullptr) {
			mid = right;
			right = nullptr;
			min2 = mid->key;
		}
		else {
			left = mid;
			mid = right;
			right = nullptr;
			min2 = mid->key;
		}
		//need to update min2 3
	}
	else 
	{
		//numChildren is 1 - leaf holds that child
		Node* leaf = left;
		if(mid != nullptr) leaf = mid;
		else if (right != nullptr) leaf = right;

		//take one item from sibiling with 3 children
		if (parent->left->numChildren() == 3 && parent->mid==this) {
			left = parent->left->right;
			mid = leaf;
		}
		else if (parent->mid->numChildren() == 3) {
			if (parent->right == this) {
				//take the right one
				if (left != nullptr) {
					mid = left;
				}
				left = parent->mid->right;
				parent->mid->right = nullptr;
				parent->mid->min3 = -1;
			}
			else {
				//take the left one
				if (mid!= nullptr) {
					left = mid;
				}
				mid = parent->mid->left;
				parent->mid->left = parent->mid->mid;
				parent->mid->mid = parent->mid->right;
				parent->mid->min2 = parent->mid->mid->key;
			}
		}
		else if (parent->right->numChildren() == 3 && parent->mid == this) {
			left = leaf;
			mid = parent->right->left;
			parent->right->left = parent->right->mid;
			parent->right->mid = parent->right->right;
			parent->right->right = nullptr;
		}

		//else move child
	}
}

void Node::updateParentMin(int data) {
	if (parent == nullptr) return;

	// Update the parent nodes
	if (parent->left == this) {
		if (parent->parent != nullptr) {
			parent->updateParentMin(data);
		}
	}
	else if (parent->mid == this) {
		parent->min2 = data;
	}
	else {
		parent->min3 = data;
	}
}

int Node::getSmallest() {
	Node *node = this;
	while (!node->isLeaf()) node = node->left;
	return node->key;
}

int Node::numChildren() {
	int c = 0;
	if (right != nullptr) c++;
	if (mid != nullptr) c++;
	if (left != nullptr) c++;
	return c;
}

bool Node::isLeaf() {
	return left == nullptr;
}

void Node::print() {
	if (isLeaf()) {
		//print
		cout << key << " ";
	}
	else {
		//print sorted, left to right
		if (left != nullptr) left->print();
		if (mid != nullptr) mid->print();
		if (right != nullptr) right->print();
	}
}