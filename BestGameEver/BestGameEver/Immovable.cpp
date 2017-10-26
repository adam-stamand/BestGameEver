#include "Immovable.h"


Immovable::Immovable()
{
}
Immovable::Immovable(float x, float y, float x_size, float y_size)
{
	this->SetXPos(x);
	this->SetYPos(y);
	this->SetXSize(x_size);
	this->SetYSize(y_size);
}


Immovable::~Immovable()
{
}
