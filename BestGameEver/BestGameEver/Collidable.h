#pragma once
#include <stdlib.h>
#include "math.h"
#include <stdio.h>
#include "Structure.h"

class Collidable
{
public:
	Collidable();
	~Collidable();

	template <typename T1, typename T2>
	bool DetectCollision(T1 &object1, T2 &object2);
	template <typename T>
	void ObjectCollision(T &object1, Structure &object2);
	template <typename T1, typename T2>
	void ObjectCollision(T1 &object1, T2 &object2);


private:
	//template <typename T>
	//virtual void Collision(T &object) = 0;
	
};


// Ellastic Collision
template <typename T1, typename T2>
void Collidable::ObjectCollision(T1 &object1, T2 &object2) {

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




template <typename T1, typename T2>
bool Collidable::DetectCollision(T1 &object1, T2 &object2) {
	int temp_x_pos = object1.GetXPos() - object2.GetXPos();
	int temp_y_pos = object1.GetYPos() - object2.GetYPos();
	float temp_x_size = (object1.GetXSize() + object2.GetXSize()) / 2;
	float temp_y_size = (object1.GetYSize() + object2.GetYSize()) / 2;
	return (abs(temp_x_pos) < temp_x_size && abs(temp_y_pos) < temp_y_size);
}


// Inelastic Collision (20% Velocity loss)
template <typename T>
void Collidable::ObjectCollision(T &object1, Structure &object2) {

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