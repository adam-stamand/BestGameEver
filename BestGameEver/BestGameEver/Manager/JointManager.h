#pragma once
#include <SFML/Graphics.hpp>
#include "Entity/Entity.h"
#include <assert.h>
#include "Box2D/Box2D.h"

// consider creating genericJoint class for jointManager to interface with


class JointManager
{
public:
	JointManager() {};
	~JointManager() {};

	struct Joint {
		std::vector<uint32_t> ids;
		b2JointType jointType;
		b2GearJoint joint;
		b2RevoluteJointDef def;
	};

	static void JointManager::RegisterJoint(Entity *entity) {
		b2JointType jointType;
		b2RevoluteJointDef defrev;
		b2JointDef def;
		b2PulleyJoint temp();
		

	};

	static void JointManager::DeRegisterJoint(int id);
	static void JointManager::EnableJoint(int id);
	static void JointManager::DisableJoint(int id);

private:
	static Entity* entities[2];//MAX_ENTITIES];
};


