#pragma once
#include <math.h>
#include <string.h>
#include "BaseComponents/SFMLGraphics/SFMLGraphicsComponent.h"
#include "BaseComponents/Message.h"
#include "Manager/SFMLManager/SFMLManager.h"



SFMLGraphicsComponent::SFMLGraphicsComponent(std::string name, std::vector<Sprite*> sprites, std::string windowName) : Component(name) {
	this->sprites = sprites;
  int rv = SFMLManager::GetWindow(windowName, this->window);
  if (rv != 0) {
    assert(0);
  }
};




void SFMLGraphicsComponent ::Update() 
{

	b2Vec2 translationItem;
	float rotationItem;
	b2Vec2 translationPart;
	float rotationPart;

	// Obtain transformation of item
  TransformMessage trans;
  PublishMessage(trans, "GetTransform");
  translationItem = trans.translation;
  rotationItem = trans.rotation;
	for (int i = 0; i < sprites.size(); i++) {

		// Obtain local transformation of sprite
		GetLocalTransformation(translationPart, rotationPart, *sprites.at(i));
		
		// Rotate sprite into world 
		ApplyRotation(translationPart, rotationPart, rotationItem);
		
		// Translate sprite to world
    ApplyTranslation(translationPart, translationItem);
			
		// Draw the sprite
		DrawSprite(
			*sprites.at(i),
			translationPart,
			rotationPart
		);
	}
}

void SFMLGraphicsComponent::ApplyTranslation(flVec2 &localTranslation, flVec2 &worldTranslation) {
  localTranslation += worldTranslation;
}

void SFMLGraphicsComponent::ApplyRotation(b2Vec2 &localPoint, float &localRotation, float &rotation) {
  float rads = DEGREES_2_RAD(rotation);
  // If the part is offcenter from item center, apply rotation matrix
	if (localPoint.x || localPoint.y) {
		float tempX = cos(rads) * localPoint.x - sin(rads) * localPoint.y;
		float tempY = sin(rads) * localPoint.x + cos(rads) * localPoint.y;
    localPoint.x = tempX;
    localPoint.y = tempY;
  }

	// Rotate
	localRotation += rotation;
}


void SFMLGraphicsComponent::GetLocalTransformation(b2Vec2 &translation, float &rotation, Sprite &sprite) {
	rotation = sprite.localRotation;
	translation = sprite.localTranslation;
}



void SFMLGraphicsComponent::DrawSprite(sf::Sprite &sprite, b2Vec2 center, float  angle) {
	sprite.setPosition(center.x, center.y);
	sprite.setRotation(angle);
  //printf("drawing x:%f, y:%f\n", center.x, center.y);
	this->window->draw(sprite);
}
