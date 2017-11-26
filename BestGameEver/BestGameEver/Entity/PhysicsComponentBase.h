#pragma once
#include "Entity/ComponentBase.h"
#include "Box2D/Box2D.h"
#include "Entity/Message.h"
#include "Globals/Globals.h"

class PhysicsComponentBase : public ComponentBase
{
public:
	PhysicsComponentBase(b2Body *body) : ComponentBase(PHYSICS){
		this->body = body;
	};

	virtual ~PhysicsComponentBase() {};
	virtual void Update(EntityBase &entity) {}


protected:
	float xPos;
	float yPos;
	float angle;
	b2Body *body; // does physics need body? What does physics even do??
};

