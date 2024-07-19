#pragma once

#include "Box2D/Box2D.h"
#include <SFML/Graphics.hpp>
#include "Entity/Entity.h"
#include "Factory/ItemType.h"

class EntityType
{
public:


	EntityType() {};
	~EntityType() {};
	std::vector<ComponentBase*> components;
};

