#pragma once
#include "ImmovableTable.h"
#include "Node.h"

class LinkedList
{
public:
	LinkedList();
	~LinkedList();
	void add(Node *object);
	Node* getNode(int);
	Node* getNode(int index, Node *n);
	Node *head;
	int listSize = 0;
	
};

