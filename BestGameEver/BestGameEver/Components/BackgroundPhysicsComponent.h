#pragma once


#include "Entity/PhysicsComponentBase.h"
#include <stdio.h>

class BackgroundPhysicsComponent : public PhysicsComponentBase
{
public:
	BackgroundPhysicsComponent(b2Body * body, float xPos, float yPos) : PhysicsComponentBase(body) {
		this->xPos = xPos;
		this->yPos = yPos;
	}

	~BackgroundPhysicsComponent() {};

	void MessageHandler(ComponentMessage &msg) {
		switch (msg.funcID) {

		case ComponentMessage::GET_TRANS: {
			ComponentMessage::Transform * params = (ComponentMessage::Transform*)msg.params;
			params->xPos = this->xPos;
			params->yPos = this->yPos;
			params->angle = 0;
			break;
		}
		}
	}
};