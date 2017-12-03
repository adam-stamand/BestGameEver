#include "RocketControlsComponent.h"


RocketControlsComponent::RocketControlsComponent() : ControlsComponentBase(this) 
{
	
	this->RegisterAction(
		{ sf::Keyboard::W },
		{ &ControlsComponent_t::MoveForward }
	);

	this->RegisterAction(
		{ sf::Keyboard::D },
		{ &ControlsComponent_t::RotateClockwise }
	);

	this->RegisterAction(
		{ sf::Keyboard::A },
		{ &ControlsComponent_t::RotateCounterClockwise }
	);

	this->RegisterAction(
		{ sf::Keyboard::L },
		{ &ControlsComponent_t::FireGun }
	);
}


void RocketControlsComponent::FireGun(EntityInterface &entity) {
	ComponentMessage::Force force(-100, b2Vec2(0, 1), b2Vec2(0, 0));
	ComponentMessage comp_msg(PHYSICS, ComponentMessage::FIRE, &force);
	entity.SendMessage(comp_msg);
}

void RocketControlsComponent::MoveForward(EntityInterface &entity) {
	ComponentMessage::Force force(-100, b2Vec2(0,1), b2Vec2(0, 0));
	ComponentMessage comp_msg(PHYSICS, ComponentMessage::APPLY_FORCE, &force);
	entity.SendMessage(comp_msg);
}


void RocketControlsComponent::RotateClockwise(EntityInterface &entity) {
	ComponentMessage::Force force(1, b2Vec2(1, 0), b2Vec2(0, -50));
	ComponentMessage comp_msg(PHYSICS, ComponentMessage::APPLY_FORCE, &force);
	entity.SendMessage(comp_msg);
}


void RocketControlsComponent::RotateCounterClockwise(EntityInterface &entity) {
	ComponentMessage::Force force(1, b2Vec2(-1, 0), b2Vec2(0, -50));
	ComponentMessage comp_msg(PHYSICS, ComponentMessage::APPLY_FORCE, &force);
	entity.SendMessage(comp_msg);
}

