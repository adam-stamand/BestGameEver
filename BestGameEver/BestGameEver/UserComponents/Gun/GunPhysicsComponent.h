#pragma once

#include "BaseComponents/Box2DPhysics/Box2DPhysicsComponent.h"


class GunPhysicsComponent : public Box2DPhysicsComponent
{
public:

	//RateLimiter rateLimiter;

  GunPhysicsComponent(std::string name, b2Body * body) : Box2DPhysicsComponent(name,body) {};//, rateLimiter(30) {};
	~GunPhysicsComponent() {};





};

