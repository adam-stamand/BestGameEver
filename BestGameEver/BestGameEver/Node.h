#pragma once
#include "Immovable.h"
template <class T>
class Node
{
public:
	Node();
	Node(T *i);
	~Node();
	Node *next;
	T *element;
};


template <class T>
Node<T>::Node()
{
	this->next = NULL;
}

template <class T>
Node<T>::Node(T *i)
{
	this->next = NULL;
	this->element = i;
}


template <class T>
Node<T>::~Node()
{
}

