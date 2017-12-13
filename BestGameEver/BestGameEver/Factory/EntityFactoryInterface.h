#pragma once
#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"

class EntityFactoryInterface
{
public:

	enum FactoryCatalogue {
		GRENADE_ENT
	};



	EntityFactoryInterface() {};
	~EntityFactoryInterface() {};



	virtual uint32_t CreateEntity(FactoryCatalogue num) = 0;
};