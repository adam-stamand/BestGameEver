#pragma once

#include "Box2D/Box2D.h"
#include "Component/ControlsComponentBase.h"
#include "Manager/EntityManager.h"
#include "Utils/RateLimiter.h"

class CharacterControlsComponent : public ControlsComponentBase<CharacterControlsComponent>
{
public:
	RateLimiter rateLimiter;
	CharacterControlsComponent();
	~CharacterControlsComponent() {};

private:
	void FireGun();
	void MoveLeft();
	void MoveRight();
};

