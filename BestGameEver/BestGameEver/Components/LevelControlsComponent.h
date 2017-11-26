#pragma once
#include "Entity/ControlsComponentBase.h"
#include "Level/EntityManager.h"
#include "Utils/RateLimiter.h"
#include <stdint.h>
#include "Box2D/Box2D.h"

class LevelControlsComponent : public ControlsComponentBase<LevelControlsComponent>, public b2ContactListener
{
public:
	LevelControlsComponent(Entity * vehicle, Entity * character);
	~LevelControlsComponent() {};

	void MessageHandler(ComponentMessage &msg) {
		switch (msg.funcID) {
		}
	};


	RateLimiter rateLimiter;

	Entity * vehicle, *character;
	bool occupied = false;
	void Enter(Entity &entity);
};

