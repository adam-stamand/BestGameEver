#pragma once

#include <stdio.h>
#include "Component/PhysicsComponentBase.h"
#include "Factory/Item.h"
#include "Globals/Globals.h"
#include "Utils/RateLimiter.h"
#include "Manager/EntityManager.h"


class GrenadePhysicsComponent2 : public PhysicsComponentBase
{
public:
	//rate limiter is fucked
	RateLimiter rateLimiter;
	uint32_t tempCnt = 0;
	GrenadePhysicsComponent2(uint32_t ticks, Item * item) : PhysicsComponentBase(item), rateLimiter(ticks) {
		rateLimiter.SetLimit(ticks);
	};
	~GrenadePhysicsComponent2() {};


	
	
	void ComponentUpdate() {
		tempCnt++;
		if (tempCnt > 100) {
			b2Vec2 point1 = this->body->GetWorldPoint(b2Vec2(0, 0));
			PhysicsRayCast ray;

			for (int i = 0; i < 50; i++) {
				float angle = DEGREES_2_RAD((360 / 50) * i);
				b2Vec2 unit_vec(sin(angle), cos(angle));
				b2Vec2 point2 = point1 + (-100.0 * unit_vec);
				Globals::world.RayCast(&ray, point1, point2);
				ray.fixture->GetBody()->ApplyLinearImpulse(-10 * unit_vec, ray.point, true);
			}
			Globals::world.DestroyBody(this->body);
			EntityManager::DeRegisterEntity(this->GetEntityID());
		}
	}



};

