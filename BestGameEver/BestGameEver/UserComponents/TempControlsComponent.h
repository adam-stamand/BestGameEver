#pragma once

#include <stdint.h>
#include "Component/ControlsComponentBase.h"
#include "Manager/EntityManager.h"
#include "Utils/RateLimiter.h"


class TempControlsComponent : public ControlsComponentBase<TempControlsComponent>
{
public:
	TempControlsComponent();
	~TempControlsComponent() {};

	RateLimiter rateLimiter;
	void Jump();
};

