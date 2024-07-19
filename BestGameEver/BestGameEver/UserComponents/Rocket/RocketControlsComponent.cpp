#include "UserComponents/Rocket/RocketControlsComponent.h"
#include "BaseComponents/Message.h"


RocketControlsComponent::RocketControlsComponent(std::string name) : SFMLControlsComponent(this, name)
{

	this->RegisterAction(
		{ sf::Keyboard::W },
		{ &RocketControlsComponent::MoveForward }
	);
  this->RegisterAction(
  { sf::Keyboard::D },
  { &RocketControlsComponent::RotateRight }
  );
  this->RegisterAction(
  { sf::Keyboard::A },
  { &RocketControlsComponent::RotateLeft }
  );
}



void RocketControlsComponent::MoveForward() {

  VectorMessage msg;
  msg.magnitude = 100;
  msg.point = b2Vec2(0, 0);
  msg.unitVec = b2Vec2(0, -1);
  PublishMessage(msg, "ApplyForce");
}


void RocketControlsComponent::RotateRight() {

  VectorMessage msg;
  msg.magnitude = 6;
  msg.point = b2Vec2(0, -100);
  msg.unitVec = b2Vec2(1, 0);
  PublishMessage(msg, "ApplyForce");
}


void RocketControlsComponent::RotateLeft() {

  VectorMessage msg;
  msg.magnitude =6;
  msg.point = b2Vec2(0, -100);
  msg.unitVec = b2Vec2(-1, 0);
  PublishMessage(msg, "ApplyForce");
}
