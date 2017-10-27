#include "ImmovableTable.h"


ImmovableTable::ImmovableTable(int granularity)
{
	this->granularity = granularity;
}

ImmovableTable::~ImmovableTable()
{
}

void ImmovableTable::add(Immovable i) {
	int x = i.GetXPos() / granularity;
	int y = i.GetYPos() / granularity;
	underlyingArray[x][y].add(&i);
}

void ImmovableTable::printCellSize(int x, int y) { //this was for testing and will probably just get deleted
	printf("%d" , underlyingArray[x][y].listSize);
}

void ImmovableTable::checkCollision(Movable *m) { //todo: make a method before this that finds all cells that Movable m is touching and call this method for each one.
	int x = m->GetXPos() / granularity;
	int y = m->GetYPos() / granularity;
	Node<Immovable> *n = underlyingArray[x][y].head;
	while (n->next != NULL) {
		//actually check if the sprites collide here
		n = n->next;
	}
}
