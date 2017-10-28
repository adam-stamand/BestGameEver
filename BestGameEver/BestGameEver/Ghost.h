#pragma once
#include "Entity.h"
#include "Movable.h"

class Ghost : public Entity,  public Movable
{
public:
	Ghost();
	~Ghost();
};

