#pragma once
// This class exists to act as an interface with the rest of the code.
// Specifically so that other code doesn't have to include Entity.h, creating circular dependency

// Acts as interface to Components

#include <array>
#include <assert.h>
#include <SFML/Graphics.hpp>

#include "Entity/Message.h"
#include "Globals/Globals.h"

class EntityBase
{
public:
	EntityBase() : id(Globals::GetID()) {};
	~EntityBase() {};

	virtual void SendMessage(ComponentMessage &msg) = 0;
	virtual void Update() = 0;

	const uint32_t id = 0;
	bool enabled = true;
};




