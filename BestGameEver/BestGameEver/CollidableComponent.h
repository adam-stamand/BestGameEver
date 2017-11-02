#pragma once

#include "Entity.h"
class CollidableComponent
{
public:
	CollidableComponent();
	virtual ~CollidableComponent() {};

	virtual void Update(Entity &entity, Entity object) = 0;
};

