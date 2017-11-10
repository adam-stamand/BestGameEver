#include "MainControlsComponent.h"




MainControlsComponent::~MainControlsComponent()
{
}



MainControlsComponent::MainControlsComponent() {

	KeyPressAction key_action;

	key_action.keys_pressed.push_back(sf::Keyboard::W);
	key_action.func_ptr = &MainControlsComponent::MoveUp;
	this->RegisterKeyPressAction(key_action);

	key_action.keys_pressed.push_back(sf::Keyboard::D);
	key_action.func_ptr = &MainControlsComponent::MoveRight;
	this->RegisterKeyPressAction(key_action);

	key_action.keys_pressed.push_back(sf::Keyboard::S);
	key_action.func_ptr = &MainControlsComponent::MoveDown;
	this->RegisterKeyPressAction(key_action);

	key_action.keys_pressed.push_back(sf::Keyboard::A);
	key_action.func_ptr = &MainControlsComponent::MoveLeft;
	this->RegisterKeyPressAction(key_action);

}


void MainControlsComponent::Update(EntityBase &entity, sf::RenderWindow &window) {
	this->CheckKeyPressActions(*this, entity);
	this->CheckEventActions(*this, entity);
}




void MainControlsComponent::MoveUp(EntityBase &entity) {
	ComponentMessage comp_msg;
	Velocity vel;
	EntityMessage ent_msg;

	vel.y = -0.0002;
	vel.x = 0;

	comp_msg.func_ID = ADD_VEL;
	comp_msg.params = &vel;

	ent_msg.comp_ID = PHYSICS;
	ent_msg.comp_msg = &comp_msg;

	entity.SendMessage(&ent_msg);
}



void MainControlsComponent::MoveRight(EntityBase &entity) {
	ComponentMessage comp_msg;
	Velocity vel;
	EntityMessage ent_msg;

	vel.y = 0;
	vel.x = 0.0002;

	comp_msg.func_ID = ADD_VEL;
	comp_msg.params = &vel;

	ent_msg.comp_ID = PHYSICS;
	ent_msg.comp_msg = &comp_msg;

	entity.SendMessage(&ent_msg);
}


void MainControlsComponent::MoveLeft(EntityBase &entity) {
	ComponentMessage comp_msg;
	Velocity vel;
	EntityMessage ent_msg;

	vel.y = 0;
	vel.x = -0.0002;

	comp_msg.func_ID = ADD_VEL;
	comp_msg.params = &vel;

	ent_msg.comp_ID = PHYSICS;
	ent_msg.comp_msg = &comp_msg;

	entity.SendMessage(&ent_msg);
}

void MainControlsComponent::MoveDown(EntityBase &entity) {
	ComponentMessage comp_msg;
	Velocity vel;
	EntityMessage ent_msg;

	vel.y = 0.0002;
	vel.x = 0;

	comp_msg.func_ID = ADD_VEL;
	comp_msg.params = &vel;

	ent_msg.comp_ID = PHYSICS;
	ent_msg.comp_msg = &comp_msg;

	entity.SendMessage(&ent_msg);
}