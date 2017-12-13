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
	ComponentMessage::Transform transform;
	ComponentMessage comp_msg(PHYSICS, ComponentMessage::GET_TRANSFORM, &transform);
	EntityManager::SendMessage(this->GetEntityID(), comp_msg);
	comp_msg.funcID = ComponentMessage::SET_TRANSFORM;
	EntityManager::SendMessage(id, comp_msg);
}

void CharacterControlsComponent::MoveRight() {
	ComponentMessage::Force force(100, b2Vec2(1, 0), b2Vec2(0, 0));
	ComponentMessage comp_msg(PHYSICS, ComponentMessage::APPLY_FORCE, &force);
	EntityManager::SendMessage(this->GetEntityID(), comp_msg);
}


void CharacterControlsComponent::MoveLeft() {
	ComponentMessage::Force force(100, b2Vec2(-1, 0), b2Vec2(0, 0));
	ComponentMessage comp_msg(PHYSICS, ComponentMessage::APPLY_FORCE, &force);
	EntityManager::SendMessage(this->GetEntityID(), comp_msg);
}


void CharacterControlsComponent::Enter() {
	if (rateLimiter.Check()) {
		ComponentMessage comp_msg(CONNECTION, ComponentMessage::ENTER, NULL);
		EntityManager::SendMessage(this->GetEntityID(), comp_msg);
	}
}

