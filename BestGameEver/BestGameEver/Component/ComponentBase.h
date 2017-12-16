#pragma once

#include "Message/ComponentMessage.h"
#include "Message/Message.h"
// USE TYPDEFS FOR ALL TYPES!!
// consider removing set entity ID function, or protecting it somehow; better than friend class // or not? // try friend function

// Consider makeing template class for messaging map

typedef uint32_t EntityID;

class ComponentBase
{

public:
	friend class Entity;

	ComponentBase(ComponentID id) : m_id(id) {};
	virtual ~ComponentBase() {};

	virtual void MessageHandler(ComponentMessage &msg) = 0;
	virtual void Update() = 0;

	ComponentID GetComponentID() { return this->m_id; };
	uint32_t GetEntityID() { return this->m_entityID; };
	
	bool IsEnabled() { return this->m_enabled; };
	void Enable(bool state) { this->m_enabled = state; };
	
private:
	void SetEntityID(EntityID entityID) { this->m_entityID = entityID; };
	bool m_enabled = true;
	const ComponentID m_id;
	EntityID m_entityID = 0;
};

