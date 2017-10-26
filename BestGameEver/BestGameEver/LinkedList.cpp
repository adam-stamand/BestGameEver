#include "LinkedList.h"
#include "ImmovableTable.h"
#include "Node.h"




LinkedList::LinkedList() 
{
	this->head = NULL;
}


LinkedList::~LinkedList()
{
}

void LinkedList::add(Node *object) { //add node to end of linkedlist
	Node * n = this->head;
	if (n == NULL) {
		n = object;
		this->head = n;
		return;
	}
	while (n->next != nullptr) {
		n = n->next;
	}
	n->next = object;
	this->listSize++;
}

Node* LinkedList::getNode(int index) { //get node at index 
	if (index >= listSize) return NULL;
	if (index == 0) return this->head;
	return this->getNode(index, this->head->next);
}

Node* LinkedList::getNode(int index, Node *n) { //get node at index 
	index--;
	if (index == 0) return n;
	return getNode(index, n->next);
}


