#pragma once

#include "Box2D/Box2D.h"
//#include "Component/ControlsComponentBase.h"
#include "Manager/EntityManager.h"
#include "Utils/RateLimiter.h"
#include "Factory/Factory.h"
#include "Factory/EntityFactory.h"
#include "UserComponents/Message/Message.h"

class CharacterControlsComponent : public ControlsComponentBase<CharacterControlsComponent>
{
public:
	RateLimiter rateLimiter;
	CharacterControlsComponent();
	~CharacterControlsComponent() {};

private:
	void Enter();
	void Grenade();
	void MoveLeft();
	void MoveRight();
};

