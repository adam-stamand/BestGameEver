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




void RocketControlsComponent::MoveForward() {
	ForceMessage comp_msg;
	comp_msg.magnitude = -100;
	comp_msg.unitVec = flVec2(0,1);
	comp_msg.point = flVec2(0, 0);
	EntityManager::SendMessage(this->GetEntityID(), comp_msg);
}


void RocketControlsComponent::RotateClockwise() {
	ForceMessage comp_msg;
	comp_msg.magnitude = 1;
	comp_msg.unitVec = flVec2(1, 0);
	comp_msg.point = flVec2(0, -50);
	EntityManager::SendMessage(this->GetEntityID(), comp_msg);
}


void RocketControlsComponent::RotateCounterClockwise() {
	ForceMessage comp_msg;
	comp_msg.magnitude = -1;
	comp_msg.unitVec = flVec2(1, 0);
	comp_msg.point = flVec2(0, -50);
	EntityManager::SendMessage(this->GetEntityID(), comp_msg);
}

