#include "CharacterControlsComponent.h"



CharacterControlsComponent::CharacterControlsComponent() : ControlsComponentBase(this), rateLimiter(30)
{

	this->RegisterAction(
		{ sf::Keyboard::D },
		{ &ControlsComponent_t::MoveRight }
	);

	this->RegisterAction(
		{ sf::Keyboard::A },
		{ &ControlsComponent_t::MoveLeft }
	);

	this->RegisterAction(
	{ sf::Keyboard::E },
	{ &ControlsComponent_t::Enter}
	);


	this->RegisterAction(
	{ sf::Keyboard::Q },
	{ &ControlsComponent_t::Grenade }
	);


}


void CharacterControlsComponent::Grenade() {
	uint32_t id = Globals::entFactoryInterface->CreateEntity(EntityFactory::GRENADE_ENT);

	TransformMessage comp_msg;
	comp_msg.SetDirection(ComponentMessage::INPUT);
	EntityManager::SendMessage(this->GetEntityID(), comp_msg);
	comp_msg.SetDirection(ComponentMessage::OUTPUT);
	EntityManager::SendMessage(id, comp_msg);
}

void CharacterControlsComponent::MoveRight() {
	ForceMessage comp_msg;
	comp_msg.magnitude = 50;
	comp_msg.unitVec = flVec2(1, 0);
	comp_msg.point = flVec2(0, 0);
	EntityManager::SendMessage(this->GetEntityID(), comp_msg);
}


void CharacterControlsComponent::MoveLeft() {
	ForceMessage comp_msg;
	comp_msg.magnitude = 50;
	comp_msg.unitVec = flVec2(-1, 0);
	comp_msg.point = flVec2(0, 0);
	EntityManager::SendMessage(this->GetEntityID(), comp_msg);
}


void CharacterControlsComponent::Enter() {
	if (rateLimiter.Check()) {
		ForceMessage comp_msg;
		comp_msg.magnitude = 50;
		comp_msg.unitVec = flVec2(-1, 0);
		comp_msg.point = flVec2(0, 0);
		EntityManager::SendMessage(this->GetEntityID(), comp_msg);
		//ComponentMessage comp_msg(CONNECTION, ComponentMessage::ENTER, NULL);
		//EntityManager::SendMessage(this->GetEntityID(), comp_msg);
	}
}

