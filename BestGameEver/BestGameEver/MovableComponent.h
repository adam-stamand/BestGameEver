#pragma once
#include "Entity.h"

class MovableComponent
{
public:
	MovableComponent();
	virtual ~MovableComponent() {};

	virtual void Update(Entity &entity) = 0;

};

