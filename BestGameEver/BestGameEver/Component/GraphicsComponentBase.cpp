#pragma once
#include "Component/GraphicsComponentBase.h"


GraphicsComponentBase::GraphicsComponentBase(sf::RenderWindow *window, Item * item) : ComponentBase(GRAPHICS) {
	this->item = item;
	this->window = window;
};


void GraphicsComponentBase::Update() {
		
	this->ComponentUpdate(); // use return value to determine if to override base update

	for (int i = 0; i < item->parts.size(); i++) {

		b2Vec2 translation = item->GetTranslation();
		float angle = *item->parts.at(i)->GetAngle();

		b2Vec2 offset(0, 0);
		b2Vec2 center = *item->parts.at(i)->GetCenter();
		float rotation = item->GetAngle();

		if (center.x || center.y) {
			offset.x = cos(rotation) * center.x - sin(rotation) * center.y;
			offset.y = sin(rotation) * center.x + cos(rotation) * center.y;
		}

		DrawSprite(
			item->parts.at(i)->GetSprite(),
			translation.x + offset.x, translation.y + offset.y,
			angle + rotation
		);
	}

		
}

void GraphicsComponentBase::MessageHandler(ComponentMessage &msg) {
	ComponentMessageHandler(msg);  // use return value to determine if to override base update
};


// move to a cpp?
void GraphicsComponentBase::DrawSprite(sf::Sprite * sprite, float x, float y, float  angle) {
	sprite->setPosition(BOX_2_SF(x), BOX_2_SF(y));
		
	sprite->setRotation(RAD_2_DEGREES(angle));
	this->window->draw(*sprite);
}
