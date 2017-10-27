#pragma once
#include "Entity.h"
#include "Immovable.h"

#include "Controllable.h"
#include <stdlib.h>
#include <stdio.h>
#define AIR_RESISTANCE	0.0005  // must be less than 1... or else you get like negative friction
#define GRAVITY		0.00003
#define FORCE		.0003f


class Movable : public Entity, public Controllable<Movable>
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
	//TODO SetSurfaceFriction
	void ObjectCollision(Movable &object1, Movable &object2);
	void ObjectCollision(Movable &object1, Immovable &object2);
	template <typename T1, typename T2>
	bool DetectCollision(T1 &object1, T2 &object2);
	void MoveUp();
	void MoveRight();
	void MoveLeft();
	void MoveDown();
	void Quit(sf::Event &evnt);

private:
	void ApplyAirResistance();
	void ApplyGravity();
	float gravity;
	float air_resistance;
	float y_vel;
	float x_vel;
};

template <typename T1, typename T2>
bool Movable::DetectCollision(T1 &object1, T2 &object2) {
	int temp_x_pos = object1.GetXPos() - object2.GetXPos();
	int temp_y_pos = object1.GetYPos() - object2.GetYPos();
	float temp_x_size = (object1.GetXSize() + object2.GetXSize()) / 2;
	float temp_y_size = (object1.GetYSize() + object2.GetYSize()) / 2;
	return (abs(temp_x_pos) < temp_x_size && abs(temp_y_pos) < temp_y_size);
}