#pragma once

#include <vector>
#include <stdint.h>
#include "Box2D/Box2D.h"

#include "Component/ComponentID.h"
//--TODO--//
// Consider cleaner way of doing enum and structs // definitely need a better way...

class ComponentMessage {
public:
	
	enum FuncID {
		GET_TRANSFORM = 0,
		SET_TRANSFORM,
		SET_VEL,
		JUMP,
		ADD_VEL,
		APPLY_FORCE,
		APPLY_IMPULSE,
		FIRE,
		ENTER,
		GET_IDS,
		CONTACT_BEGIN,
		CONTACT_END,
		DISABLE,
		ENABLE,
		GET_BODY,
		ENABLE_BODY
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


	struct IDPair{
		uint32_t idA;
		uint32_t idB;
	};


	struct Contact {
		uint32_t primaryID;
		std::vector<uint32_t> secondaryVec;
	};

	struct Body {
		b2Body * body;
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

