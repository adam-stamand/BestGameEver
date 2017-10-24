#pragma once
#pragma once
#include "Entity.h"
#include <stdlib.h>
#include <stdio.h>
class Immovable : public Entity
{
public:
	Immovable(float x, float y, float x_size, float y_size);
	~Immovable();
};

