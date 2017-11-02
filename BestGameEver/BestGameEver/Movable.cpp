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



void Movable::SetGravity(float grav) {
	this->gravity = grav;
}

void Movable::SetAirResistance(float resist) {
	this->air_resistance = resist;
}

float Movable::GetGravity() {
	return this->gravity;
}

float Movable::GetAirResistance() {
	return this->air_resistance;
}



void Movable::Accelerate(Direction dir, float force, Entity &entity) {
	float temp_vel;

	switch (dir) {
	case UP:
		temp_vel = entity.GetYVel() + force / entity.GetMass();
		entity.SetYVel(temp_vel);
		break;

	case DOWN:
		temp_vel = entity.GetYVel() - force / entity.GetMass();
		entity.SetYVel(temp_vel);
		break;

	case LEFT:
		temp_vel = entity.GetXVel() - force / entity.GetMass();
		entity.SetXVel(temp_vel);
		break;

	case RIGHT:
		temp_vel = entity.GetXVel() + force / entity.GetMass();
		entity.SetXVel(temp_vel);
		break;
	}


}

void Movable::ApplyAirResistance(Entity &entity) {
	float temp_vel;

	temp_vel = entity.GetYVel() - (entity.GetYVel() * this->air_resistance);
	entity.SetYVel(temp_vel);
	temp_vel = entity.GetXVel() - (entity.GetXVel() * this->air_resistance);
	entity.SetYVel(temp_vel);
}


void Movable::ApplyGravity(Entity &entity) {
	float temp_vel;
	temp_vel = entity.GetYVel() - this->gravity;
	entity.SetYVel(temp_vel);
}


void Movable::Update(Entity &entity) {
	this->ApplyGravity(entity);
	this->ApplyAirResistance(entity);
	
	entity.SetXPos(entity.GetXPos() + entity.GetXVel());
	entity.SetYPos(entity.GetYPos() + entity.GetYVel());
}
