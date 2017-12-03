#include "ConnectionControlsComponent.h"



ConnectionControlsComponent::ConnectionControlsComponent() : ControlsComponentBase(this), rateLimiter(20)
{

	this->RegisterAction(
	{ sf::Keyboard::E },
	{ &ControlsComponent_t::Enter }
	);

}


void ConnectionControlsComponent::Enter(EntityInterface &entity) {
	if (rateLimiter.Check()) {
		ComponentMessage comp_msg(CONNECTION, ComponentMessage::ENTER, NULL);
		entity.SendMessage(comp_msg);
	}
}

