#pragma once

#include <assert.h>
#include <array>
#include <SFML/Graphics.hpp>

#include "Entity/Message.h"
#include "Entity/ComponentBase.h"
#include "Entity/EntityInterface.h"
#include "Globals/Globals.h"
#include "Entity/ComponentID.h"



class Entity : public EntityInterface
{
public:
	typedef std::array<ComponentBase*, NUM_COMP> ComponentArray;
	typedef std::vector<ComponentBase*> ComponentVec;

	Entity(ComponentVec comps);
	~Entity() {};

	void SendMessage(ComponentMessage &msg);
	void Update();

	void AddComponent(ComponentBase * component);
	void RemoveComponent(ComponentID id);
	void EnableComponent(ComponentID id);
	void DisableComponent(ComponentID id);

	ComponentArray components = { 0 }; // check that all elements are put to 0
};


