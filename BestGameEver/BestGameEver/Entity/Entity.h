#pragma once

#include <assert.h>
#include <array>
#include <SFML/Graphics.hpp>
#include "Globals/Globals.h"
#include "Component/ComponentBase.h"


// Allow for variable number of components; Generic component

class Entity
{
public:
	typedef std::array<ComponentBase*, NUM_COMP> ComponentArray;
	typedef std::vector<ComponentBase*> ComponentVec;

	Entity() : id(Globals::GetEntityID()) {}
	~Entity() {};

	void Init(ComponentVec comps);
	uint32_t GetID();
	bool IsEnabled();
	void Enable(bool state);

	void SendMessage(ComponentMessage &msg);
	void Update();

	void AddComponent(ComponentBase * component);
	void RemoveComponent(ComponentID id);
	void EnableComponent(ComponentID id);
	void DisableComponent(ComponentID id);

private:
	ComponentArray components = { 0 };
	const uint32_t id = 0; // 0 is treated as invalid id number
	bool enabled = true;
};


