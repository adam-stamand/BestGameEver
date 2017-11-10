#pragma once
#include "Entity/ComponentMessage.h"
#include <SFML/Graphics.hpp>
#include "Entity/EntityBase.h"

class Component
{
public:

	enum ComponentID {
		PHYSICS = 0,
		CONTROLS,
		GRAPHICS,
		NUM_COMP
	};


	Component() {};
	virtual ~Component() {};

	virtual void Update(EntityBase &entity, sf::RenderWindow &window) = 0;
	virtual void MessageHandler(ComponentMessage *comp_msg) = 0;

	ComponentID ID;
};

