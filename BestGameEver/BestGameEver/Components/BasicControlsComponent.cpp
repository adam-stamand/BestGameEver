#include "BasicControlsComponent.h"



BasicControlsComponent::BasicControlsComponent() : ControlsComponentBase(this) 
{

	this->RegisterAction(
		{ sf::Keyboard::W },
		{ &ControlsComponent_t::MoveUp }
	);

	this->RegisterAction(
		{ sf::Keyboard::D },
		{ &ControlsComponent_t::MoveRight }
	);

	this->RegisterAction(
		{ sf::Keyboard::S },
		{ &ControlsComponent_t::MoveDown }
	);

	this->RegisterAction(
		{ sf::Keyboard::A },
		{ &ControlsComponent_t::MoveLeft }
	);

	this->RegisterAction(
		{ sf::Event::MouseButtonPressed },
		{ &ControlsComponent_t::Teleport }
	);

}




void BasicControlsComponent::Teleport(sf::Event &evnt, EntityBase &entity) {
	ComponentMessage comp_msg;
	EntityMessage ent_msg;
	b2Vec2 position(evnt.mouseButton.x, evnt.mouseButton.y);
	

	comp_msg.func_ID = SET_POS;
	comp_msg.params = &position;

	ent_msg.comp_ID = PHYSICS;
	ent_msg.comp_msg = &comp_msg;

	entity.SendMessage(&ent_msg);

}

void BasicControlsComponent::MoveUp(EntityBase &entity) {
	ComponentMessage comp_msg;
	b2Vec2 force(0, -100);
	EntityMessage ent_msg;

	comp_msg.func_ID = APPLY_FORCE;
	comp_msg.params = &force;

	ent_msg.comp_ID = PHYSICS;
	ent_msg.comp_msg = &comp_msg;

	entity.SendMessage(&ent_msg);
}



void BasicControlsComponent::MoveRight(EntityBase &entity) {
	ComponentMessage comp_msg;
	EntityMessage ent_msg;
	b2Vec2 force(100, 0);

	comp_msg.func_ID = APPLY_FORCE;
	comp_msg.params = &force;

	ent_msg.comp_ID = PHYSICS;
	ent_msg.comp_msg = &comp_msg;

	entity.SendMessage(&ent_msg);
}


void BasicControlsComponent::MoveLeft(EntityBase &entity) {
	ComponentMessage comp_msg;
	EntityMessage ent_msg;
	b2Vec2 force(-100, 0);

	comp_msg.func_ID = APPLY_FORCE;
	comp_msg.params = &force;

	ent_msg.comp_ID = PHYSICS;
	ent_msg.comp_msg = &comp_msg;

	entity.SendMessage(&ent_msg);
}

void BasicControlsComponent::MoveDown(EntityBase &entity) {
	ComponentMessage comp_msg;
	EntityMessage ent_msg;
	b2Vec2 force(0, 100);

	comp_msg.func_ID = APPLY_FORCE;
	comp_msg.params = &force;

	ent_msg.comp_ID = PHYSICS;
	ent_msg.comp_msg = &comp_msg;

	entity.SendMessage(&ent_msg);
}