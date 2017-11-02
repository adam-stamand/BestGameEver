#pragma once
#include <stdlib.h>
#include "math.h"
#include <stdio.h>
#include "Structure.h"
#include "CollidableComponent.h"

class Collidable : public CollidableComponent
{
public:
	Collidable();
	~Collidable();

	void Update(Entity &entity, Entity &object);


private:

	bool DetectCollision(Entity &object1, Entity &object2);
	void ObjectCollision(Entity &object1, Entity &object2);


};

