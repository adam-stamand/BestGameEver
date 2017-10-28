#include "Structure.h"



Structure::Structure(float x, float y, float x_size, float y_size)
{
	this->SetXPos(x);
	this->SetYPos(y);
	this->SetXSize(x_size);
	this->SetYSize(y_size);
}


Structure::~Structure()
{
}
