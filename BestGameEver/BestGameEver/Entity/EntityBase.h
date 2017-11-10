#pragma once
// This class exists to act as an interface with the rest of the code.
// Specifically so that other code doesn't have to include Entity.h, creating circular dependency
#include "EntityMessage.h"
#include <SFML/Graphics.hpp>


class EntityBase
{
public:
	


	EntityBase() {};
	~EntityBase() {};

	virtual void SendMessage(EntityMessage * msg) = 0;
	virtual void Update(sf::RenderWindow &window) = 0;

	float x_pos;
	float y_pos;

};


