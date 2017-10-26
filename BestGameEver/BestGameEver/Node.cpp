#include "Node.h"


Node::Node()
{
	this->next = NULL;
}

Node::Node(Immovable &i)
{
	this->next = NULL;
	this->element = i;
}


Node::~Node()
{
}
