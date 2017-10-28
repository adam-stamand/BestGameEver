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
	void add(Entity i);

	void checkCollision(Entity *m);
	int granularity;
	LinkedList<Entity> underlyingArray[100][100]; //eventually 100's will be replaced by (level size / granularity)
};




