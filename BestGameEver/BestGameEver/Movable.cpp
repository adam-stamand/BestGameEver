#include "Movable.h"


Movable::Movable() :
	gravity(GRAVITY),
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

void Movable::Accelerate(Direction dir, float force) {
	switch (dir) {
	case UP:
		this->y_vel += force / GetMass();
		break;

	case DOWN:
		this->y_vel -= force / GetMass();
		break;

	case LEFT:
		this->x_vel -= force / GetMass();
		break;

	case RIGHT:
		this->x_vel += force / GetMass();
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


void Movable::UpdatePosition() {
	//this->ApplyGravity();
	this->ApplyAirResistance();
	this->SetXPos(GetXPos() + this->x_vel);
	this->SetYPos(GetYPos() + this->y_vel);
}
/*
//need to add a jump cooldown when deltaTime is implemented. atm a jump will have the force of many.
bool Movable::CanJump(Movable &object) { //object needs to be a list of objects
	if (this->GetYPos() < 1) return true;
	if (this->GetYPos() - object.GetYPos() < 20 && abs(this->GetXPos() - object.GetXPos()) < 20) return true;//super temporary. this will eventually work with a list (or tree) of objects and hopefully use variables based on objects size rather than "20"
	return false;
}
*/


// Ellastic Collision
void Movable::ObjectCollision(Movable &object1, Movable &object2) {

	int deltax = object1.GetXPos() - object2.GetXPos();
	int deltay = object1.GetYPos() - object2.GetYPos();

	if (abs(deltax) > abs(deltay)) {
		object2.SetXPos(object2.GetXPos() - ((deltax > 0) - (deltax < 0)) * (object2.GetXSize() - abs(deltax) + 1));
	}
	else {
		object2.SetYPos(object2.GetYPos() - ((deltay > 0) - (deltay < 0)) * (object2.GetYSize() - abs(deltay) + 1));
	}

	float vx1i = object1.GetXVel();
	float vy1i = object1.GetYVel();
	float vx2i = object2.GetXVel();
	float vy2i = object2.GetYVel();


	object1.SetXVel(
		(((object1.GetMass() - object2.GetMass()) / (object1.GetMass() + object2.GetMass())) * vx1i) +
		(((2 * object2.GetMass()) / (object1.GetMass() + object2.GetMass())) * vx2i)
	);

	object1.SetYVel(
		(((object1.GetMass() - object2.GetMass()) / (object1.GetMass() + object2.GetMass())) * vy1i) +
		(((2 * object2.GetMass()) / (object1.GetMass() + object2.GetMass())) * vy2i)
	);


	object2.SetXVel(
		(((object2.GetMass() - object1.GetMass()) / (object1.GetMass() + object2.GetMass())) * vx2i ) +
		(((2 * object1.GetMass()) / (object1.GetMass() + object2.GetMass())) * vx1i)
	);

	// The above math was incorrect. Fixed now, so we'll see if this condition is still necessary
	//if (object1.GetYPos() <= object2.GetYPos()) { //i had to add this conditional. without it, the object would follow the player when he jumped
	object2.SetYVel(
		(((object2.GetMass() - object1.GetMass()) / (object1.GetMass() + object2.GetMass())) * vy2i) +
		(((2 * object1.GetMass()) / (object1.GetMass() + object2.GetMass())) * vy1i)
	);
	

}




// Inelastic Collision (20% Velocity loss)
void Movable::ObjectCollision(Movable &object1, Immovable &object2) {



	object1.SetXVel(-object1.GetXVel() * 0.8);
	if (object1.GetXPos() < 0) {
		object1.SetXPos(0);
	}
	else if (object1.GetXPos() > 780) {
		object1.SetXPos(780);
	}


	object1.SetYVel(-object1.GetYVel() * 0.8);
	if (object1.GetYPos() < 0) {
		object1.SetYPos(0);
	}
	else if (object1.GetYPos() > 580) {
		object1.SetYPos(580);
	}


	if (object1.GetYPos() < 0) {
		object1.SetYPos(0);
	}
	else if (object1.GetYPos() > 580) {
		object1.SetYPos(580);
	}
	if (object1.GetXPos() < 0) {
		object1.SetXPos(0);
	}
	else if (object1.GetXPos() > 780) {
		object1.SetXPos(780);
	}
}


bool Movable::DetectCollision(Movable &object1, Movable &object2) {
	int temp_x_pos = object1.GetXPos() - object2.GetXPos();
	int temp_y_pos = object1.GetYPos() - object2.GetYPos();
	return (abs(temp_x_pos) < object2.GetXSize() && abs(temp_y_pos) < object2.GetYSize());
}
