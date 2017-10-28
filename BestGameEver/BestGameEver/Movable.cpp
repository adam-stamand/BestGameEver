#include "Movable.h"


Movable::Movable() :
	gravity(-GRAVITY),
	air_resistance(AIR_RESISTANCE)
{
}

Movable::Movable(float grav, float resist) {
	this->gravity = grav;
	this->air_resistance = resist;
}

Movable::~Movable() {
}

void Movable::SetYVel(float y) {
	this->y_vel = y;
}

void Movable::SetXVel(float x) {
	this->x_vel = x;
}

float Movable::GetXVel() {
	return this->x_vel;
}


float Movable::GetYVel() {
	return this->y_vel;
}

void Movable::SetGravity(float grav) {
	this->gravity = grav;
}

void Movable::SetAirResistance(float resist) {
	this->air_resistance = resist;
}



void Movable::Accelerate(Direction dir, float force, Entity &entity) {
	switch (dir) {
	case UP:
		this->y_vel += force / entity.GetMass();
		break;

	case DOWN:
		this->y_vel -= force / entity.GetMass();
		break;

	case LEFT:
		this->x_vel -= force / entity.GetMass();
		break;

	case RIGHT:
		this->x_vel += force / entity.GetMass();
		break;
	}


}

void Movable::ApplyAirResistance() {
	this->y_vel -= this->y_vel * this->air_resistance;
	this->x_vel -= this->x_vel * this->air_resistance;
}


void Movable::ApplyGravity() {
	this->y_vel -= this->gravity;
}


void Movable::UpdatePosition(Entity &entity) {
	this->ApplyGravity();
	this->ApplyAirResistance();
	
	entity.SetXPos(entity.GetXPos() + this->x_vel);
	entity.SetYPos(entity.GetYPos() + this->y_vel);
}
