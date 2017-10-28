#include "Collidable.h"



Collidable::Collidable()
{
}


Collidable::~Collidable()
{
}


/*
//need to add a jump cooldown when deltaTime is implemented. atm a jump will have the force of many.
bool Movable::CanJump(Movable &object) { //object needs to be a list of objects
if (this->GetYPos() < 1) return true;
if (this->GetYPos() - object.GetYPos() < 20 && abs(this->GetXPos() - object.GetXPos()) < 20) return true;//super temporary. this will eventually work with a list (or tree) of objects and hopefully use variables based on objects size rather than "20"
return false;
}
*/



