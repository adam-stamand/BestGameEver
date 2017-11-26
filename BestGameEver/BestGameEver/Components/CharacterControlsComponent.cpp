#include "CharacterControlsComponent.h"



CharacterControlsComponent::CharacterControlsComponent() : ControlsComponentBase(this)
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
	{ sf::Keyboard::L },
	{ &ControlsComponent_t::FireGun }
	);	

}


CharacterControlsComponent::~CharacterControlsComponent()
{
}


void CharacterControlsComponent::MoveRight(Entity &entity) {
	ComponentMessage::Force force(100, b2Vec2(1, 0), b2Vec2(0, 0));
	ComponentMessage comp_msg(PHYSICS, ComponentMessage::APPLY_FORCE, &force);
	entity.SendMessage(comp_msg);
}

void CharacterControlsComponent::MoveLeft(Entity &entity) {
	ComponentMessage::Force force(100, b2Vec2(-1, 0), b2Vec2(0, 0));
	ComponentMessage comp_msg(PHYSICS, ComponentMessage::APPLY_FORCE, &force);
	entity.SendMessage(comp_msg);
}

void CharacterControlsComponent::FireGun(Entity &entity) {
	ComponentMessage::Force force(1, b2Vec2(0, 1), b2Vec2(0, 0));
	ComponentMessage comp_msg(PHYSICS, ComponentMessage::APPLY_FORCE, &force);
	entity.SendMessage(comp_msg);
}
