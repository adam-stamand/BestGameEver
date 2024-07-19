#pragma once

#include <stdint.h>
#include "Component/ControlsComponentBase.h"
#include "Manager/EntityManager.h"
#include "Utils/RateLimiter.h"


class ConnectionControlsComponent : public ControlsComponentBase<ConnectionControlsComponent>
{
public:
	ConnectionControlsComponent();
	~ConnectionControlsComponent() {};

	RateLimiter rateLimiter;
	void Enter();
};

