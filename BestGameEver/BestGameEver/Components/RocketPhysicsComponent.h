#pragma once
#include "Entity/PhysicsComponentBase.h"


class RocketPhysicsComponent : public PhysicsComponentBase
{
public:
	RocketPhysicsComponent(b2Body *body, b2World *world) : PhysicsComponentBase(body, world) {}
	~RocketPhysicsComponent() {};


	void MessageHandler(ComponentMessage *msg) {
		b2Vec2 * temp;
		b2Vec2 unit_vec;
		float *force;
		switch (msg->func_ID) {

		case APPLY_FORCE:
			force = ((float*)msg->params);
			unit_vec = this->body->GetWorldVector(b2Vec2(0, 1));
			this->body->ApplyForceToCenter((*force * unit_vec), true);
			break;
		case ROTATE:
			force = ((float*)msg->params);
			unit_vec = this->body->GetWorldVector(b2Vec2(1, 0));
			this->body->ApplyForce((*force * unit_vec), this->body->GetWorldPoint(b2Vec2(0, -50)), true);

			//this->body->SetAngularVelocity(*force);
			break;

		}
	}



};

