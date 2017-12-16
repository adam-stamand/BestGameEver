#include "GunControlsComponent.h"



GunControlsComponent::GunControlsComponent() : ControlsComponentBase(this)
{
	this->RegisterAction(
		{ sf::Event::MouseButtonPressed },
		{ &ControlsComponent_t::FireGun }
	);
}



void GunControlsComponent::FireGun(sf::Event &evnt) {
	/*
	ForceMessage comp_msg;
	comp_msg.magnitude = -100;
	comp_msg.unitVec = flVec2(0, 1);
	comp_msg.point = flVec2(0, 0);
	EntityManager::SendMessage(this->GetEntityID(), comp_msg);
	*/

}

