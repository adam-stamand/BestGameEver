#pragma once

#include "BaseComponents/Box2DPhysics/Box2DPhysicsComponent.h"



class BasicPhysicsComponent : public Box2DPhysicsComponent
{
public:
  BasicPhysicsComponent(std::string name, b2Body * body) : Box2DPhysicsComponent(body, name) {}
	~BasicPhysicsComponent() {};

};

