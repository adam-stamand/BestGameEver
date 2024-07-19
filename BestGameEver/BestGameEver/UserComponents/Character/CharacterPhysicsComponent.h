#pragma once

#include <stdint.h>
#include "Component/PhysicsComponentBase.h"
#include "Globals/Globals.h"
#include "Utils/RateLimiter.h"
#include "Factory/Item.h"
#include "UserComponents/Message/Message.h"


class CharacterPhysicsComponent : public PhysicsComponentBase
{
	typedef void(CharacterPhysicsComponent::*MessageHandler_p)(ComponentMessage &comp_msg);
public:

	RateLimiter rateLimiter;
	CharacterPhysicsComponent(Item * item);
	~CharacterPhysicsComponent() {};

	bool ComponentMessageHandler(ComponentMessage &msg);




private:
	std::map<std::string, MessageHandler_p> messageHandlerMap;
};


