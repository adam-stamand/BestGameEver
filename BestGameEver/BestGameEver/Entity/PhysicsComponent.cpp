#include "PhysicsComponent.h"


/*

// Ellastic Collision
void PhysicsComponent::ObjectCollision(Entity &object1, Entity &object2) {

	int deltax = object1.x_pos - object2.x_pos;
	int deltay = object1.y_pos - object2.y_pos;

	if (abs(deltax) > abs(deltay)) {
		object1.x_pos = (object1.x_pos - ((deltax > 0) - (deltax < 0)) * (object1.GetXSize() - abs(deltax) + 1));
	}
	else {
		object1.y_pos = (object1.y_pos - ((deltay > 0) - (deltay < 0)) * (object1.GetYSize() - abs(deltay) + 1));
	}

	if (this->mass == 0) {
		int xDiff = object1.x_pos - object2.x_pos + object1.GetXSize();
		int yDiff = object1.y_pos - object2.y_pos + object1.GetYSize();

		if (abs(xDiff) > object2.GetXSize()) {
			if (fabs(this->x_vel) <= .01) {
				this->x_vel = ((object1.x_pos >= object2.x_pos + object2.GetXSize() / 2) ? .001 : -.001);
			}
			else this->x_vel = (-this->x_vel * 0.8);
		}
		if (abs(yDiff) > object2.GetYSize()) {
			if (fabs(this->y_vel) <= .01) {
				this->y_vel = ((object1.y_pos >= object2.y_pos + object2.GetYSize() / 2) ? .001 : -.001);
			}
			else this->y_vel = (-this->y_vel * 0.8);
		}
	}
	else {

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
			(((object2.GetMass() - object1.GetMass()) / (object1.GetMass() + object2.GetMass())) * vx2i) +
			(((2 * object1.GetMass()) / (object1.GetMass() + object2.GetMass())) * vx1i)
		);

		// The above math was incorrect. Fixed now, so we'll see if this condition is still necessary
		//if (object1.GetYPos() <= object2.GetYPos()) { //i had to add this conditional. without it, the object would follow the player when he jumped
		object2.SetYVel(
			(((object2.GetMass() - object1.GetMass()) / (object1.GetMass() + object2.GetMass())) * vy2i) +
			(((2 * object1.GetMass()) / (object1.GetMass() + object2.GetMass())) * vy1i)
		);
	}



}



bool PhysicsComponent::DetectCollision(Entity &object1, Entity &object2) {
	int temp_x_pos = object1.x_pos - object2.x_pos;
	int temp_y_pos = object1.y_pos - object2.y_pos;
	float temp_x_size = (object1.GetXSize() + object2.GetXSize()) / 2;
	float temp_y_size = (object1.GetYSize() + object2.GetYSize()) / 2;
	return (abs(temp_x_pos) < temp_x_size && abs(temp_y_pos) < temp_y_size);
}

*/




//void PhysicsComponent::testCollision() {
	//puts("collided");
//}

void PhysicsComponent::ApplyAirResistance() {
	this->y_vel -= (this->y_vel * this->air_resistance);
	this->x_vel -= (this->x_vel * this->air_resistance);
}


void PhysicsComponent::ApplyGravity() {
	this->y_vel = this->y_vel - this->gravity;
}


