#include "LevelControlsComponent.h"



LevelControlsComponent::LevelControlsComponent(Entity * vehicle, Entity * character) : ControlsComponentBase(this), rateLimiter(20)
{
	
	vehicle->DisableComponent(CONTROLS);
	this->character = character;
	this->vehicle = vehicle;

	this->RegisterAction(
	{ sf::Keyboard::E },
	{ &ControlsComponent_t::Enter}
	);
}


void LevelControlsComponent::Enter(Entity &entity) {
	
	if (rateLimiter.Check()) {
		if (this->occupied) {
			vehicle->DisableComponent(CONTROLS);
			EntityManager::EnableEntity(this->character->id);
			
			ComponentMessage::Transform trans;
			
			ComponentMessage comp_msg(PHYSICS, ComponentMessage::GET_TRANS, &trans);
			this->vehicle->SendMessage(comp_msg);

			comp_msg.funcID = ComponentMessage::SET_TRANS;
			this->character->SendMessage(comp_msg);

			this->occupied = false;
		}
		else {
			vehicle->EnableComponent(CONTROLS);
			EntityManager::DisableEntity(this->character->id);
			this->occupied = true;
		}
	}

}

