#pragma once

#include <assert.h>
#include <array>
#include <SFML/Graphics.hpp>
#include <string>

#include "Component/ComponentBase.h"
#include "Globals/Globals.h"
#include "Manager/DebugManager.h"

//--TODO--//
// Change constructor to require input string


// Allow for variable number of components; Generic component // maybe


class Entity
{
	typedef std::array<ComponentBase*, NUM_COMP> ComponentArray;
	typedef std::vector<ComponentBase*> ComponentVec;

public:
	Entity() : id(Globals::GetEntityID()) {}
	Entity(std::string str) : id(Globals::GetEntityID()) { entityName = str; } // make only constructor // delete other one
	~Entity() {};

	void SendMessage(ComponentMessage &msg);
	void Update();

	void AddComponent(ComponentVec comps);
	void RemoveComponent(ComponentID id);
	void EnableComponent(ComponentID id);
	void DisableComponent(ComponentID id);

	uint32_t GetID();
	bool IsEnabled();
	void Enable(bool state);

	std::string GetName() { return entityName; }
	std::string PrintEntity();

private:
	ComponentArray components = { 0 };
	const uint32_t id = 0; // 0 is treated as invalid id number
	bool enabled = true;
	std::string entityName = "Unnamed";
};


