#pragma once
#include "Entity.h"


#define AIR_RESISTANCE	0.0005  // must be less than 1... or else you get like negative friction
#define GRAVITY		0.00003
#define FORCE		.0003f


class Movable
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
	void UpdatePosition(Entity &entity);
	void Accelerate(Direction dir, float force, Entity &entity);
	float GetXVel();
	float GetYVel();
	void SetXVel(float x);
	void SetYVel(float y);
	void SetGravity(float grav);
	void SetAirResistance(float resist);
	//TODO SetSurfaceFriction


private:
	void ApplyAirResistance();
	void ApplyGravity();
	float gravity;
	float air_resistance;
	float y_vel;
	float x_vel;
};

