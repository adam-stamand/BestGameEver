#pragma once
#include <vector>
#include "Utils/Node.h"
#include "Entity/Entity.h"
#include "Utils/LinkedList.h"

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




