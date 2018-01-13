#include "UserComponents/Character/CharacterPhysicsComponent.h"



CharacterPhysicsComponent::CharacterPhysicsComponent(Item * item) : PhysicsComponentBase(item), rateLimiter(30), 
	messageHandlerMap({
	})
{}



bool CharacterPhysicsComponent::ComponentMessageHandler(ComponentMessage &comp_msg) {
	auto iter = messageHandlerMap.find(comp_msg.funcName);
	if (iter != messageHandlerMap.end()) {
		(this->*iter->second)(comp_msg);
		return true;
	}
	return false;
}


