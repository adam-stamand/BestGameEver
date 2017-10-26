#pragma once
#include "Immovable.h"
#include "LinkedList.h"

class ImmovableTable
{
public:	
	ImmovableTable(int granularity);
	~ImmovableTable();
	void add(Immovable i);
private:
	int granularity;
	LinkedList underlyingArray[100][100];
};

