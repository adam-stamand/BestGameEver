#include "CharacterControlsComponent.h"
#include "BaseComponents/Message.h"


CharacterControlsComponent::CharacterControlsComponent(std::string name) : SFMLControlsComponent(this, name)//, rateLimiter(30)
{

	this->RegisterAction(
		{ sf::Keyboard::D },
		{ &ControlsComponent_t::MoveRight }
	);

	this->RegisterAction(
		{ sf::Keyboard::A },
		{ &ControlsComponent_t::MoveLeft }
	);

	this->RegisterAction(
	{ sf::Keyboard::E },
	{ &ControlsComponent_t::Enter}
	);


	this->RegisterAction(
	{ sf::Keyboard::Q },
	{ &ControlsComponent_t::Grenade }
	);


}


void CharacterControlsComponent::Grenade() {

}

void CharacterControlsComponent::MoveRight() {
  VectorMessage msg;
  msg.magnitude = 50;
  msg.point = b2Vec2(0, 0);
  msg.unitVec = b2Vec2(1, 0);
  PublishMessage(msg, "ApplyForce");
}


void CharacterControlsComponent::MoveLeft() {
  VectorMessage msg;
  msg.magnitude = 50;
  msg.point = b2Vec2(0, 0);
  msg.unitVec = b2Vec2(-1, 0);
  PublishMessage(msg, "ApplyForce");
}


void CharacterControlsComponent::Enter() {

}

