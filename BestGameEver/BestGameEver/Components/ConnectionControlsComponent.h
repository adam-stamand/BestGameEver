#pragma once
#include "Entity/ControlsComponentBase.h"
#include "Level/EntityManager.h"
#include "Utils/RateLimiter.h"
#include "Entity/Message.h"
#include <stdint.h>
#include "Box2D/Box2D.h"

class ConnectionControlsComponent : public ControlsComponentBase<ConnectionControlsComponent>
{
public:
	ConnectionControlsComponent();
	~ConnectionControlsComponent() {};

	void MessageHandler(ComponentMessage &msg) {
		switch (msg.funcID) {
		}
	};



	RateLimiter rateLimiter;
	void Enter(EntityInterface &entity);
};

