#pragma once

#include "Component/ComponentMessage.h"
#include "Component/ComponentID.h"

// consider removing set entity ID function, or protecting it somehow; better than friend class

class ComponentBase
{
public:
	friend class Entity;
	ComponentBase(ComponentID id) : id(id) {};
	virtual ~ComponentBase() {};

	virtual void MessageHandler(ComponentMessage &msg) = 0;
	virtual void Update() = 0;

	ComponentID GetComponentID() { return this->id; };
	uint32_t GetEntityID() { return this->entityID; };
	
	bool IsEnabled() { return this->enabled; };
	void Enable(bool state) { this->enabled = state; };
	
private:
	void SetEntityID(uint32_t entityID) { this->entityID = entityID; };
	bool enabled = true;
	const ComponentID id;
	uint32_t entityID;
};

