#include "Collidable.h"



Collidable::Collidable()
{
}


Collidable::~Collidable()
{
}

void Collidable::Update(Entity &entity, Entity &object) {

	if (DetectCollision(entity, object)) {
		ObjectCollision(entity, object);
	}
}

// Ellastic Collision
void Collidable::ObjectCollision(Entity &object1, Entity &object2) {

	int deltax = object1.GetXPos() - object2.GetXPos();
	int deltay = object1.GetYPos() - object2.GetYPos();

	if (abs(deltax) > abs(deltay)) {
		object1.SetXPos(object1.GetXPos() - ((deltax > 0) - (deltax < 0)) * (object1.GetXSize() - abs(deltax) + 1));
	}
	else {
		object1.SetYPos(object1.GetYPos() - ((deltay > 0) - (deltay < 0)) * (object1.GetYSize() - abs(deltay) + 1));
	}

	if (object2.GetMass() == 0) {
		int xDiff = object1.GetXPos() - object2.GetXPos() + object1.GetXSize();
		int yDiff = object1.GetYPos() - object2.GetYPos() + object1.GetYSize();

		if (abs(xDiff) > object2.GetXSize()) {
			if (fabs(object1.GetXVel()) <= .01) {
				object1.SetXVel((object1.GetXPos() >= object2.GetXPos() + object2.GetXSize() / 2) ? .001 : -.001);
			}
			else object1.SetXVel(-object1.GetXVel() * 0.8);
		}
		if (abs(yDiff) > object2.GetYSize()) {
			if (fabs(object1.GetYVel()) <= .01) {
				object1.SetYVel((object1.GetYPos() >= object2.GetYPos() + object2.GetYSize() / 2) ? .001 : -.001);
			}
			else object1.SetYVel(-object1.GetYVel() * 0.8);
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



bool Collidable::DetectCollision(Entity &object1, Entity &object2) {
	int temp_x_pos = object1.GetXPos() - object2.GetXPos();
	int temp_y_pos = object1.GetYPos() - object2.GetYPos();
	float temp_x_size = (object1.GetXSize() + object2.GetXSize()) / 2;
	float temp_y_size = (object1.GetYSize() + object2.GetYSize()) / 2;
	return (abs(temp_x_pos) < temp_x_size && abs(temp_y_pos) < temp_y_size);
}



/*
//need to add a jump cooldown when deltaTime is implemented. atm a jump will have the force of many.
bool Movable::CanJump(Movable &object) { //object needs to be a list of objects
if (this->GetYPos() < 1) return true;
if (this->GetYPos() - object.GetYPos() < 20 && abs(this->GetXPos() - object.GetXPos()) < 20) return true;//super temporary. this will eventually work with a list (or tree) of objects and hopefully use variables based on objects size rather than "20"
return false;
}
*/



