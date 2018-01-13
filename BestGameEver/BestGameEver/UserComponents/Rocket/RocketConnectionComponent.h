#pragma once

#include "Component/ConnectionComponentBase.h"
#include "Manager/Manager.h"
#include "UserComponents/Message/Message.h"

// move to generic component

class RocketConnectionComponent : public ConnectionComponentBase
{

public:


	enum CharacterConnection {
		ROCKET_CONNECTION,
		CAR_CONNECTION,
		BALLOON_CONNECTION,
		GUN_CONNECTION,
		SEGMENT_CONNECTION,
		NUM_CONNECTION
	};


	RocketConnectionComponent(std::vector<EntityID> entityIDs);

	~RocketConnectionComponent() {};


	void Test(ComponentMessage &msg);

	
	bool touchingRocket = false;
	bool touchingBalloon = false;
	bool touchingCar = false;
	bool inCar = false;
	bool inBalloon = false;
	bool inRocket = false;
	bool onGround = false;
	bool occupied = false;
	EntityID vehicleID = 0;
	b2RevoluteJointDef jointDef;
	b2RevoluteJoint* m_joint;


	typedef void(RocketConnectionComponent::*MessageHandler_p)(ComponentMessage &comp_msg);
	bool ComponentMessageHandler(ComponentMessage &msg);



private:
	std::map<std::string, MessageHandler_p> messageHandlerMap;

	


};