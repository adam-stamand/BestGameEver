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
}


void RocketControlsComponent::MoveForward(EntityBase &entity) {
	ComponentMessage comp_msg;
	EntityMessage ent_msg;
	float force = -100;


	comp_msg.func_ID = APPLY_FORCE;
	comp_msg.params = &force;

	ent_msg.comp_ID = PHYSICS;
	ent_msg.comp_msg = &comp_msg;

	entity.SendMessage(&ent_msg);
}


void RocketControlsComponent::RotateClockwise(EntityBase &entity) {
	ComponentMessage comp_msg;
	EntityMessage ent_msg;
	float force = 1;


	comp_msg.func_ID = ROTATE;
	comp_msg.params = &force;

	ent_msg.comp_ID = PHYSICS;
	ent_msg.comp_msg = &comp_msg;

	entity.SendMessage(&ent_msg);
}


void RocketControlsComponent::RotateCounterClockwise(EntityBase &entity) {
		ComponentMessage comp_msg;
	EntityMessage ent_msg;
	float force = -1;


	comp_msg.func_ID = ROTATE;
	comp_msg.params = &force;

	ent_msg.comp_ID = PHYSICS;
	ent_msg.comp_msg = &comp_msg;

	entity.SendMessage(&ent_msg);
}

