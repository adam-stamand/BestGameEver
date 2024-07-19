#include "UserComponents/Character/CharacterConnectionComponent.h"




CharacterConnectionComponent::CharacterConnectionComponent(std::vector<EntityID> entityIDs)
	: ConnectionComponentBase(entityIDs),
	messageHandlerMap({{ "TEST", &CharacterConnectionComponent::Test }}) 
{
	this->entityIDs = entityIDs;

	EntityManager::DisableComponent(entityIDs[ROCKET_CONNECTION], CONTROLS);
	EntityManager::DisableComponent(entityIDs[GUN_CONNECTION], CONTROLS);
	EntityManager::DisableComponent(entityIDs[GUN_CONNECTION], PHYSICS);
	EntityManager::DisableComponent(entityIDs[CAR_CONNECTION], CONTROLS);

};

void CharacterConnectionComponent::Test(ComponentMessage &comp_msg) {


	EntityID primary;
	EntityID secondary;


	if (inRocket) {

		TestMessage * test = static_cast<TestMessage*>(&comp_msg);
		puts(test->str.c_str());

		EntityManager::DisableComponent(vehicleID, CONTROLS);
		//EntityManager::DisableComponent(entityIDs[GUN_CONNECTION], CONTROLS);
		//EntityManager::DisableComponent(entityIDs[GUN_CONNECTION], PHYSICS);
		EntityManager::EnableComponent(this->GetEntityID(), PHYSICS);
		EntityManager::EnableComponent(this->GetEntityID(), GRAPHICS);

		TransformMessage trans;
		trans.SetDirection(ComponentMessage::OUTPUT);
		EntityManager::SendMessage(vehicleID, trans);

		ItemMessage item;
		EntityManager::SendMessage(this->GetEntityID(), item);
		item.item->body->SetActive(true);

		trans.angle = 0; // we don't want to rotate the character
		trans.SetDirection(ComponentMessage::INPUT);
		EntityManager::SendMessage(this->GetEntityID(), trans);

		this->inRocket = false;
		
	}

	else if (ConnectionManager::GetContactConnection("TEST_CONNECTION", primary, secondary)) {
		
		TestMessage * test = static_cast<TestMessage*>(&comp_msg);
		puts(test->str.c_str());

		EntityManager::EnableComponent(secondary, CONTROLS);
		//EntityManager::EnableComponent(entityIDs[GUN_CONNECTION], CONTROLS);
		//EntityManager::EnableComponent(entityIDs[GUN_CONNECTION], PHYSICS);
		EntityManager::DisableComponent(this->GetEntityID(), PHYSICS);
		EntityManager::DisableComponent(this->GetEntityID(), GRAPHICS);
		ItemMessage itemMessage;
		EntityManager::SendMessage(this->GetEntityID(), itemMessage);
		itemMessage.item->body->SetActive(false);
		vehicleID = secondary;
		this->inRocket = true;
	}
	
}


bool CharacterConnectionComponent::ComponentMessageHandler(ComponentMessage &comp_msg) {
	auto iter = messageHandlerMap.find(comp_msg.funcName);
	if (iter != messageHandlerMap.end()) {
		(this->*iter->second)(comp_msg);
		return true;
	}
	return false;
}