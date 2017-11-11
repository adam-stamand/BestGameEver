#pragma once
#include "Entity/EntityBase.h"

class ComponentBase
{
public:

	enum ComponentID {
		PHYSICS = 0,
		CONTROLS,
		GRAPHICS,
		NUM_COMP
	};


	ComponentBase() {};
	virtual ~ComponentBase() {};

	virtual void Update(EntityBase &entity) = 0;
	virtual void MessageHandler(ComponentMessage *comp_msg) = 0;

	ComponentID ID;
};

