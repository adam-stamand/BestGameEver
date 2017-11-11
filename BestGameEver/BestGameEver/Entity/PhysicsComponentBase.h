#pragma once
#include "Entity/ComponentBase.h"
#include "Box2D/Box2D.h"

class PhysicsComponentBase : public ComponentBase
{
public:
	PhysicsComponentBase(b2Body *body, b2World *world) {
		this->body = body;
		this->world = world;
		this->ID = PHYSICS;
	};

	virtual ~PhysicsComponentBase() {};


	virtual void Update(EntityBase &entity) {
		entity.x_pos = this->body->GetPosition().x;
		entity.y_pos = this->body->GetPosition().y;
		entity.angle = this->body->GetAngle();
	}


protected:
	b2Body *body;
	b2World *world;
};

