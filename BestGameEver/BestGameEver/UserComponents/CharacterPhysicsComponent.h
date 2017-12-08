#pragma once

#include <stdint.h>
#include "Component/PhysicsComponentBase.h"
#include "Globals/Globals.h"
#include "Utils/RateLimiter.h"


class CharacterPhysicsComponent : public PhysicsComponentBase
{
public:

	RateLimiter rateLimiter;
	CharacterPhysicsComponent(Item * item) : PhysicsComponentBase(item), rateLimiter(30) {};
	~CharacterPhysicsComponent() {};


	void ComponentMessageHandler(ComponentMessage &msg) {

		switch (msg.funcID) {

		case ComponentMessage::FIRE: {
			if (rateLimiter.Check()) {
				PhysicsRayCast ray;
				ComponentMessage::Force * params = (ComponentMessage::Force*)msg.params;
				b2Vec2 unit_vec = this->body->GetWorldVector(params->vec);
				b2Vec2 point1 = this->body->GetWorldPoint(b2Vec2(0, 0));
				b2Vec2 point2 = point1 + (-100.0 * unit_vec);
				Globals::world.RayCast(&ray, point1, point2);
				ray.fixture->GetBody()->ApplyLinearImpulse(params->force * unit_vec, ray.point, true);
			}
			break;
		}

		}
	}
};
