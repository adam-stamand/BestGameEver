#pragma once
#include "Entity.h"
#include "MovableComponent.h"

#define AIR_RESISTANCE	0.0005  // must be less than 1... or else you get like negative friction
#define GRAVITY		0.00003
#define FORCE		.0003f


class Movable : public MovableComponent
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

	void Update(Entity &entity);
	void Accelerate(Direction dir, float force, Entity &entity);




	//TODO SetSurfaceFriction


private:
	float GetGravity();
	float GetAirResistance();
	void SetGravity(float grav);
	void SetAirResistance(float resist);
	void ApplyAirResistance(Entity &entity);
	void ApplyGravity(Entity &entity);
	float gravity;
	float air_resistance;
	float surface_friciton;

};

