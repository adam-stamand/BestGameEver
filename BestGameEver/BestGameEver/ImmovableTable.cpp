#include "ImmovableTable.h"

ImmovableTable::ImmovableTable(int granularity)
{
	this->granularity = granularity;
}

ImmovableTable::~ImmovableTable()
{
}

void ImmovableTable::add(Immovable i) {
	float x = i.GetXPos();
	float y = i.GetYPos();
	//	underlyingArray[x][y]
}
