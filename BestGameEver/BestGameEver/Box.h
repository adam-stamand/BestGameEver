#pragma once
#include "Collidable.h"

class Box : public Entity, public Collidable, public Movable
{
public:
	Box();
	~Box();

	void Collision(Movable &object) { this->ObjectCollision(*this, object); };
	void Collision(Entity &object) { this->ObjectCollision(*this, object); };
	void PrintSomething() { puts("box"); };

};

