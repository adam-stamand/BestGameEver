#pragma once
#include "Entity.h"
#include "Immovable.h"
#include <stdlib.h>
#include <stdio.h>
#define AIR_RESISTANCE	0.0005  // must be less than 1... or else you get like negative friction
#define GRAVITY		0.000009
class Movable : public Entity
{
public:
	Movable();
	Movable(float grav, float resist);
	~Movable();

	enum Direction {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};
	void UpdatePosition();
	void Accelerate(Direction dir, float force);
	float GetXVel();
	float GetYVel();
	void SetXVel(float x);
	void SetYVel(float y);
	void SetGravity(float grav);
	void SetAirResistance(float resist);
	void ObjectCollision(Movable &object1, Movable &object2);
	void ObjectCollision(Movable &object1, Immovable &object2);
	bool DetectCollision(Movable &object1, Movable &object2);
	bool DetectCollision(Movable &object1, Immovable &object2);

private:
	void ApplyAirResistance();
	void ApplyGravity();
	float gravity;
	float air_resistance;
	float y_vel;
	float x_vel;
};

