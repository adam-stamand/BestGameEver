#include "MainPhysicsComponent.h"




MainPhysicsComponent::~MainPhysicsComponent()
{
}


/*
void MainPhysicsComponent::Accelerate(Direction dir, float force, Entity &entity) {
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



void MainPhysicsComponent::ApplyAirResistance(Entity &entity) {
	float temp_vel;

	temp_vel = entity.GetYVel() - (entity.GetYVel() * this->air_resistance);
	entity.SetYVel(temp_vel);
	temp_vel = entity.GetXVel() - (entity.GetXVel() * this->air_resistance);
	entity.SetYVel(temp_vel);
}


void MainPhysicsComponent::ApplyGravity(Entity &entity) {
	float temp_vel;
	temp_vel = entity.GetYVel() - this->gravity;
	entity.SetYVel(temp_vel);
}
*/