#include "UserComponents/Basic/BasicControlsComponent.h"
#include "BaseComponents/Message.h"


BasicControlsComponent::BasicControlsComponent(std::string name) : SFMLControlsComponent(this, name)
{

	this->RegisterAction(
		{ sf::Keyboard::W },
		{ &BasicControlsComponent::MoveForward }
	);
  this->RegisterAction(
  { sf::Keyboard::S },
  { &BasicControlsComponent::MoveBackward }
  );
  this->RegisterAction(
  { sf::Keyboard::D },
  { &BasicControlsComponent::RotateRight }
  );
  this->RegisterAction(
  { sf::Keyboard::A },
  { &BasicControlsComponent::RotateLeft }
  );
}



void BasicControlsComponent::MoveForward() {

  VectorMessage msg;
  msg.magnitude = 50;
  msg.point = b2Vec2(0, 0);
  msg.unitVec = b2Vec2(0, -1);
  PublishMessage(msg, "ApplyForce");
}

void BasicControlsComponent::MoveBackward() {

  VectorMessage msg;
  msg.magnitude = 50;
  msg.point = b2Vec2(0, 0);
  msg.unitVec = b2Vec2(0, 1);
  PublishMessage(msg, "ApplyForce");
}

void BasicControlsComponent::RotateRight() {

  VectorMessage msg;
  msg.magnitude = 3;
  msg.point = b2Vec2(0, -100);
  msg.unitVec = b2Vec2(1, 0);
  PublishMessage(msg, "ApplyForce");
}


void BasicControlsComponent::RotateLeft() {

  VectorMessage msg;
  msg.magnitude = 3;
  msg.point = b2Vec2(0, -100);
  msg.unitVec = b2Vec2(-1, 0);
  PublishMessage(msg, "ApplyForce");
}
