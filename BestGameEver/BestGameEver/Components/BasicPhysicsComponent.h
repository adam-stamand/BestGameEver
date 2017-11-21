#pragma once
#include "Entity/PhysicsComponentBase.h"
#include <stdio.h>

class BasicPhysicsComponent : public PhysicsComponentBase
{
public:
	BasicPhysicsComponent(b2Body *body) : PhysicsComponentBase(body) {};
	~BasicPhysicsComponent() {};


	void MessageHandler(ComponentMessage *msg) {
		b2Vec2 * temp;
		switch (msg->func_ID) {

		case APPLY_FORCE:
			temp = ((b2Vec2*)msg->params);
			this->body->ApplyForceToCenter(*temp, true);
			break;
		case SET_POS:
			temp = ((b2Vec2*)msg->params);
			this->body->SetTransform(*temp, this->body->GetAngle());
			break;

		}
	};


};

