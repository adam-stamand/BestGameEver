#pragma once
// This class exists to act as an interface with the rest of the code.
// Specifically so that other code doesn't have to include Entity.h, creating circular dependency
#include "Message.h"
#include <SFML/Graphics.hpp>


class EntityBase
{
public:
	EntityBase() { this->id = EntityBase::counter++; };
	~EntityBase() {};

	virtual void SendMessage(EntityMessage * msg) = 0;
	virtual void Update() = 0;

	int id; // consider making a const
	static uint32_t counter;

	float x_pos = 0;
	float y_pos = 0;
	float angle = 0;
};


