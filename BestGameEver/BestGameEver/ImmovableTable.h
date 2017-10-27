#pragma once
#include <vector>
#include "Immovable.h"
#include "LinkedList.h"
#include "Movable.h"
#include "Node.h"


class ImmovableTable
{
public:	
	ImmovableTable(int granularity);
	~ImmovableTable();
	void printCellSize(int x, int y);
	void add(Immovable i);

	void checkCollision(Movable *m);
	int granularity;
	LinkedList<Immovable> underlyingArray[100][100]; //eventually 100's will be replaced by (level size / granularity)
};




