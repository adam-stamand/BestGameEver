#pragma once

#include <stdint.h>
#include "Box2D/Box2D.h"
#include "Entity/ComponentID.h"




class ComponentMessage {
public:
	
	enum FuncID {
		GET_TRANS = 0,
		SET_TRANS,
		SET_VEL,
		ADD_VEL,
		APPLY_FORCE,
		APPLY_IMPLUSE,
		FIRE,
		ENTER,
		GET_IDS,
		CONTACT_BEGIN,
		CONTACT_END,
		DISABLE,
		ENABLE
	};

	struct Transform {
		float xPos;
		float yPos;
		float angle;
	};

	struct Velocity {
		float xVel;
		float yVel;
	};

	struct Contact {
		uint32_t idA;
		uint32_t idB;
	};


	struct Force { 
		float force;
		b2Vec2 vec;
		b2Vec2 point;
		Force(float inputForce, b2Vec2 inputVec, b2Vec2 inputPoint) {
			force = inputForce;
			vec = inputVec;
			point = inputPoint;
		}
	};


	ComponentMessage(ComponentID compID, FuncID funcID, void *params) {
		this->compID = compID;
		this->funcID = funcID;
		this->params = params;
	}

	~ComponentMessage() {}


	ComponentID compID;
	FuncID funcID;
	void *params = NULL;

};


class EntityMessage : public ComponentMessage{

public:

	EntityMessage(uint32_t entityID, ComponentID compID, FuncID funcID, void *params) : ComponentMessage(compID,funcID, params) {
		this->entityID = entityID;
	}

	~EntityMessage() {}

	uint32_t entityID = 0;
};


