#include "TempControlsComponent.h"



TempControlsComponent::TempControlsComponent() : ControlsComponentBase(this), rateLimiter(20)
{
	this->RegisterAction(
	{ sf::Keyboard::W },
	{ &ControlsComponent_t::Jump }
	);
}


void TempControlsComponent::Jump() {

	if (rateLimiter.Check()) {
		ComponentMessage::Force force(-10, b2Vec2(0, 1), b2Vec2(0, 0));
		ComponentMessage comp_msg(CONNECTION, ComponentMessage::JUMP, &force);
		EntityManager::SendMessage(this->GetEntityID(), comp_msg);
	}
}

