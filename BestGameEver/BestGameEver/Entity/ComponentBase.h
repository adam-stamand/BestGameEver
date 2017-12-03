#pragma once

#include "Entity/EntityInterface.h"
#include "Entity/ComponentID.h"
#include "Entity/Message.h"

class ComponentBase
{
public:

	ComponentBase(ComponentID id) { this->id = id; };
	virtual ~ComponentBase() {};

	virtual void MessageHandler(ComponentMessage &msg) = 0;
	virtual void Update(EntityInterface &entity) = 0;

	bool enabled = true;
	ComponentID id;
};

