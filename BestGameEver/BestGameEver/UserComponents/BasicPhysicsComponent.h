#pragma once

#include <stdio.h>
#include "Component/PhysicsComponentBase.h"



class BasicPhysicsComponent : public PhysicsComponentBase
{
public:
	BasicPhysicsComponent(Item * item) : PhysicsComponentBase(item) {};
	~BasicPhysicsComponent() {};


};

