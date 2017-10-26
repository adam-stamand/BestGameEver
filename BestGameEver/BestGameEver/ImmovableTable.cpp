#include "ImmovableTable.h"



ImmovableTable::ImmovableTable(int granularity)
{
	this->granularity = granularity;
}


ImmovableTable::~ImmovableTable()
{
}

void ImmovableTable::add(Immovable i) {
	int x = i.GetXPos();
	int y = i.GetXPos();
//	underlyingArray[x][y]
}

