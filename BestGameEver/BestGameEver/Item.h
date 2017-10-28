#pragma once
#include "Entity.h"
#include "Movable.h"
#include "Collidable.h"


class Item : public Movable, public Entity, public Collidable
{

public:
	Item();
	~Item();

	template <typename T>
	bool CheckCollision(T &object) { return this->DetectCollision(*this, object); };

	template <typename T>
	void Collision(T &object) { this->ObjectCollision(*this, object); };

};

