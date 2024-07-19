#include "ConnectionControlsComponent.h"



ConnectionControlsComponent::ConnectionControlsComponent() : ControlsComponentBase(this), rateLimiter(20)
{
	this->RegisterAction(
		{ sf::Keyboard::E },
		{ &ControlsComponent_t::Enter }
	);
}


void ConnectionControlsComponent::Enter() {
	if (rateLimiter.Check()) {
		ComponentMessage comp_msg(CONNECTION, ComponentMessage::ENTER, NULL);
		//EntityManager::SendMessage(this->GetEntityID(), comp_msg);
	}
}

