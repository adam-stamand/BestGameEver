#pragma once
#include "Controllable.h"
#include "Movable.h"
#include "Entity.h"
#include "Collidable.h"


class Player : public Movable, public Entity, public Collidable, public Controllable<Player>
{
public:
	Player();

	~Player();
	template <typename T>  
	void Collision(T &object) { this->ObjectCollision(*this, object); };
	template <typename T>
	bool CheckCollision(T &object) { return this->DetectCollision(*this, object); };
};

