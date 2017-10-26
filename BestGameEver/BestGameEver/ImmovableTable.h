#pragma once
#include <vector>
#include "Immovable.h"
#include "LinkedList.h"


class ImmovableTable
{
public:	
	ImmovableTable(int granularity);
	~ImmovableTable();

	void add(Immovable i);
	int granularity;
	LinkedList<Immovable> underlyingArray;
};




