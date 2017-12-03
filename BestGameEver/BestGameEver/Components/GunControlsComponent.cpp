#include "GunControlsComponent.h"



GunControlsComponent::GunControlsComponent() : ControlsComponentBase(this)
{


	this->RegisterAction(
		{ sf::Event::MouseButtonPressed },
		{ &ControlsComponent_t::FireGun }
	);


}


GunControlsComponent::~GunControlsComponent()
{
}


void GunControlsComponent::FireGun(sf::Event &evnt, EntityInterface &entity) {
	ComponentMessage::Force force(-100, b2Vec2(0, 1), b2Vec2(0, 0));
	ComponentMessage comp_msg(PHYSICS, ComponentMessage::FIRE, &force);
	entity.SendMessage(comp_msg);
}

