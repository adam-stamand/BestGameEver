#pragma once
#include "Entity/PhysicsComponent.h"
#include "Entity/EntityMessage.h"
#include <stdio.h>

class MainPhysicsComponent : public PhysicsComponent
{
public:
	MainPhysicsComponent(float mass, float gravity, float air_resistance) : PhysicsComponent(mass, gravity, air_resistance) {};
	~MainPhysicsComponent();


	void MessageHandler(ComponentMessage *msg) {
		switch (msg->func_ID) {
		case ADD_VEL:
			Velocity * temp = ((Velocity*)msg->params);
			this->x_vel += temp->x;
			this->y_vel += temp->y;
		}
	};

private:

};

