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




void BasicControlsComponent::Teleport(sf::Event &evnt, Entity &entity) {
	ComponentMessage comp_msg;
	EntityMessage ent_msg;
	b2Vec2 position(evnt.mouseButton.x, evnt.mouseButton.y);
	

	comp_msg.funcID = SET_POS;
	comp_msg.params = &position;

	ent_msg.compID = PHYSICS;
	ent_msg.comp_msg = &comp_msg;

	entity.SendMessage(ent_msg);

}

void BasicControlsComponent::MoveUp(Entity &entity) {
	ComponentMessage comp_msg;
	b2Vec2 force(0, -100);
	EntityMessage ent_msg;

	comp_msg.funcID = APPLY_FORCE;
	comp_msg.params = &force;

	ent_msg.compID = PHYSICS;
	ent_msg.comp_msg = &comp_msg;

	entity.SendMessage(ent_msg);
}



void BasicControlsComponent::MoveRight(Entity &entity) {
	ComponentMessage comp_msg;
	EntityMessage ent_msg;
	b2Vec2 force(100, 0);

	comp_msg.funcID = APPLY_FORCE;
	comp_msg.params = &force;

	ent_msg.compID = PHYSICS;
	ent_msg.comp_msg = &comp_msg;

	entity.SendMessage(ent_msg);
}


void BasicControlsComponent::MoveLeft(Entity &entity) {
	ComponentMessage comp_msg;
	EntityMessage ent_msg;
	b2Vec2 force(-100, 0);

	comp_msg.funcID = APPLY_FORCE;
	comp_msg.params = &force;

	ent_msg.compID = PHYSICS;
	ent_msg.comp_msg = &comp_msg;

	entity.SendMessage(ent_msg);
}

void BasicControlsComponent::MoveDown(Entity &entity) {
	ComponentMessage comp_msg;
	EntityMessage ent_msg;
	b2Vec2 force(0, 100);

	comp_msg.funcID = APPLY_FORCE;
	comp_msg.params = &force;

	ent_msg.compID = PHYSICS;
	ent_msg.comp_msg = &comp_msg;

	entity.SendMessage(ent_msg);
}