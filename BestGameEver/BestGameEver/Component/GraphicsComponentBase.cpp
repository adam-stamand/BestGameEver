#pragma once
#include "Component/GraphicsComponentBase.h"


GraphicsComponentBase::GraphicsComponentBase(sf::RenderWindow *window, Item * item) : ComponentBase(GRAPHICS) {
	this->item = item;
	this->window = window;
};


void GraphicsComponentBase::Update() 
{
	this->ComponentUpdate(); // use return value to determine if to override base update

	b2Vec2 translationItem;
	float rotationItem;
	b2Vec2 translationPart;
	float rotationPart;

	// Obtain transformation of item
	GetWorldTransformation(translationItem, rotationItem, *item);

	for (int i = 0; i < item->parts.size(); i++) {

		// Obtain local transformation of part
		GetLocalTransformation(translationPart, rotationPart, *item->parts.at(i));
		
		// Transform part into world coordinates
		Transform(translationPart, rotationPart, rotationItem);
		
		// Translate part to item
		translationPart += translationItem;
			
		// Draw the part
		DrawSprite(
			*item->parts.at(i)->GetSprite(),
			translationPart,
			rotationPart
		);
	}
}


void GraphicsComponentBase::Transform(b2Vec2 &localPoint, float &localRotation, float &rotation) {

	// If the part is offcenter from item center, apply rotation matrix
	if (localPoint.x || localPoint.y) {
		localPoint.x = cos(rotation) * localPoint.x - sin(rotation) * localPoint.y;
		localPoint.y = sin(rotation) * localPoint.x + cos(rotation) * localPoint.y;
	}

	// Rotate
	localRotation += rotation;
}


void GraphicsComponentBase::GetLocalTransformation(b2Vec2 &translation, float &rotation, Part &part) {
	rotation = part.GetAngle();
	translation = part.GetCenter();
}


void GraphicsComponentBase::GetWorldTransformation(b2Vec2 &translation, float &rotation, Item &item) {
	translation = item.GetTranslation();
	rotation = item.GetAngle();
}


void GraphicsComponentBase::MessageHandler(ComponentMessage &msg) {
	ComponentMessageHandler(msg);  // use return value to determine if to override base update
};


void GraphicsComponentBase::DrawSprite(sf::Sprite &sprite, b2Vec2 center, float  angle) {
	sprite.setPosition(BOX_2_SF(center.x), BOX_2_SF(center.y));
	sprite.setRotation(RAD_2_DEGREES(angle));
	this->window->draw(sprite);
}
