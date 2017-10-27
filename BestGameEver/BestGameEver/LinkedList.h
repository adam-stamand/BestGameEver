#pragma once
#include "Node.h"
template <class T>
class LinkedList
{
public:
	LinkedList();
	~LinkedList();
	void add(T *object);
	Node<T>* getNode(int);
	Node<T>* getNode(int index, Node<T> *n);
	Node<T> *head;
	int listSize;
	
};

template <class T>
void LinkedList<T>::add(T *object) { //add node to end of linkedlist
	Node<T> * n = this->head;
	Node<T> *newNode = new Node<T>[1];
	if (n == NULL) {
		n = newNode;
		n->element = object;
		this->head = n;
		this->listSize++;
		return;
	}
	while (n->next != nullptr) {
		n = n->next;
	}
	n->element = object;
	this->listSize++;
}

template <class T>
LinkedList<T>::LinkedList()
{
	this->head = NULL;
	this->listSize = 0;
}


template <class T>
LinkedList<T>::~LinkedList()
{
}


template <class T>
Node<T>* LinkedList<T>::getNode(int index) { //get node at index 
	if (index == 0) return this->head;
	return this->getNode(index, this->head->next);
}

template <class T>
Node<T>* LinkedList<T>::getNode(int index, Node<T> *n) { //get node at index 
	if (n == NULL) return NULL;
	index--;
	if (index == 0) return n;
	return getNode(index, n->next);
}

