#pragma once

#include "Component/Message/ComponentMessage.h"


// consider removing set entity ID function, or protecting it somehow; better than friend class // or not? // try friend function

// Consider how to make message map a base member

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
	
protected:
	virtual bool ComponentMessageHandler(ComponentMessage &msg) { return false; };

private:
	void SetEntityID(EntityID entityID) { this->m_entityID = entityID; };
	bool m_enabled = true;
	const ComponentID m_id;
	EntityID m_entityID = 0;
};

