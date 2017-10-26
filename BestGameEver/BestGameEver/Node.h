#pragma once
#include "Immovable.h"

class Node
{
public:
	Node();
	Node(Immovable &i);
	~Node();
	Node *next;
	Immovable element;
};

