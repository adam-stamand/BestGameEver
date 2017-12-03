#pragma once
// This class exists to act as an interface with the rest of the code.
// Specifically so that other code doesn't have to include Entity.h, creating circular dependency

// Acts as interface to Components

#include <array>
#include <assert.h>
#include <SFML/Graphics.hpp>
#include "Globals/Globals.h"

#include "Entity/Message.h"

class EntityInterface
{
public:
	EntityInterface() : id(Globals::GetID()) {};
	~EntityInterface() {};

	virtual void SendMessage(ComponentMessage &msg) = 0;
	virtual void Update() = 0;

	//virtual void AddComponent(ComponentBase * component) = 0;
	virtual void RemoveComponent(ComponentID id) = 0;
	virtual void EnableComponent(ComponentID id) = 0;
	virtual void DisableComponent(ComponentID id) = 0;

	const uint32_t id = 0;
	bool enabled = true;
};




