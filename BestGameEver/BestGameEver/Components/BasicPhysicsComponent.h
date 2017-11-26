#pragma once
#include "Entity/PhysicsComponentBase.h"
#include <stdio.h>

class BasicPhysicsComponent : public PhysicsComponentBase
{
public:
	BasicPhysicsComponent(b2Body *body) : PhysicsComponentBase(body) {};
	~BasicPhysicsComponent() {};


	void MessageHandler(ComponentMessage &msg) {
		b2Vec2 * temp;
		switch (msg.funcID) {

		case ComponentMessage::APPLY_FORCE: {
			temp = ((b2Vec2*)msg.params);
			this->body->ApplyForceToCenter(*temp, true);
			break;

		}
		case ComponentMessage::GET_TRANS: {
			ComponentMessage::Transform * params = (ComponentMessage::Transform*)msg.params;
			b2Vec2 temp;
			temp.x = this->body->GetPosition().x;
			temp.y = this->body->GetPosition().y;
			float tempAngle = this->body->GetAngle();
			params->xPos = temp.x;
			params->yPos = temp.y;
			params->angle = tempAngle;

			break;
		}
			

		}
	};


};

