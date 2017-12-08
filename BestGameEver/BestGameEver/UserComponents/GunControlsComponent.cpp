#include "GunControlsComponent.h"



GunControlsComponent::GunControlsComponent() : ControlsComponentBase(this)
{
	this->RegisterAction(
		{ sf::Event::MouseButtonPressed },
		{ &ControlsComponent_t::FireGun }
	);
}



void GunControlsComponent::FireGun(sf::Event &evnt) {
	ComponentMessage::Force force(-100, b2Vec2(0, 1), b2Vec2(0, 0));
	ComponentMessage comp_msg(PHYSICS, ComponentMessage::FIRE, &force);
	EntityManager::SendMessage(this->GetEntityID(), comp_msg);
}

