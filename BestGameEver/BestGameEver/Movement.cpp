#include "Movement.h"


Movement::Movement(float mass, float max_vel) {
	this->mass = mass;
	this->max_vel = max_vel;
}

Movement::~Movement() {
}

void Movement::SetXPos(float x) {
	this->x_pos = x;
}


void Movement::SetYPos(float y) {
	this->y_pos = y;
}


float Movement::GetXPos() {
	return this->x_pos;
}

float Movement::GetYPos() {
	return this->y_pos;
}

void Movement::SetYVel(float y) {
	this->y_vel = y;
}

void Movement::SetXVel(float x) {
	this->x_vel = x;
}

float Movement::GetXVel() {
	return this->x_vel;
}


float Movement::GetYVel() {
	return this->y_vel;
}

void Movement::Push(Direction dir, float force) {

	switch (dir) {
	case UP:
		this->y_vel += force / this->mass;
		break;

	case DOWN:
		this->y_vel -= force / this->mass;
		break;

	case LEFT:
		this->x_vel -= force / this->mass;
		break;

	case RIGHT:
		this->x_vel += force / this->mass;
		break;
	}
}

void Movement::ApplyFriction() {
	this->y_vel -= this->y_vel * FRICTION;
	this->x_vel -= this->x_vel * FRICTION;
}


void Movement::ApplyGravity() {
	this->y_vel -= GRAVITY;
}

void Movement::UpdatePosition() {
	this->ApplyGravity();
	this->ApplyFriction();
	this->x_pos += this->x_vel;
	this->y_pos += this->y_vel;
}
//need to add a jump cooldown when deltaTime is implemented. atm a jump will have the force of many.
bool Movement::CanJump(Movement &object) { //object needs to be a list of objects
	if (this->GetYPos() < 1) return true;
	if (this->GetYPos() - object.GetYPos() < 20 && abs(this->GetXPos() - object.GetXPos()) < 20) return true;//super temporary. this will eventually work with a list (or tree) of objects and hopefully use variables based on objects size rather than "20"
	return false;
}
