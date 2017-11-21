#pragma once
#include "Entity/ComponentBase.h"
#include "Box2D/Box2D.h"

class PhysicsComponentBase : public ComponentBase
{
public:
	PhysicsComponentBase(b2Body *body) {
		this->body = body;
		this->ID = PHYSICS;
	};

	virtual ~PhysicsComponentBase() {};


	//TODO Consider keeping everything in box values to prevent unnecessary conversions
	// Pretty sure its not possible actually. Graphics needs it in SF coords
	virtual void Update(EntityBase &entity) {
		entity.x_pos = BOX_2_SF(this->body->GetPosition().x);
		entity.y_pos = BOX_2_SF(this->body->GetPosition().y);
		entity.angle = this->body->GetAngle();
	}


protected:
	b2Body *body;
};

