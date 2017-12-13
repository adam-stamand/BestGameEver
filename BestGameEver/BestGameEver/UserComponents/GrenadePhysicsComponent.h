#pragma once

#include <stdint.h>
#include "Component/PhysicsComponentBase.h"
#include "Globals/Globals.h"
#include "Utils/RateLimiter.h"
#include "Factory/Item.h"


class GrenadePhysicsComponent : public PhysicsComponentBase
{
public:

	RateLimiter rateLimiter;

	GrenadePhysicsComponent(uint32_t ticks, Item* item) : PhysicsComponentBase(item), rateLimiter(ticks) {};
	~GrenadePhysicsComponent() {};


	void ComponentUpdate() {
		if (rateLimiter.Check()) {
			b2Vec2 point1 = this->body->GetWorldPoint(b2Vec2(0, 0));
			PhysicsRayCast ray;

			for (int i = 0; i < 50; i++) {
				float angle = DEGREES_2_RAD((360 / 50) * i);
				b2Vec2 unit_vec(sin(angle), cos(angle));
				b2Vec2 point2 = point1 + (-100.0 * unit_vec);
				Globals::world.RayCast(&ray, point1, point2);
				ray.fixture->GetBody()->ApplyLinearImpulse(100 * unit_vec, ray.point, true);
			}
		}	
	}

	
};

