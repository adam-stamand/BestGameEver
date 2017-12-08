#pragma once

#include <math.h>
#include <string.h>
#include "Component/ComponentBase.h"
#include "Manager/EntityManager.h"
#include "Factory/Item.h"


// Figure out what to do with items; Should everything use items? How to use with and without body?

class GraphicsComponentBase : public ComponentBase
{
public:
	GraphicsComponentBase(sf::RenderWindow *window, Item * item) : ComponentBase(GRAPHICS) {
		this->item = item;
		this->window = window;
	};

	~GraphicsComponentBase() {};


	void Update() {
		
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

		ComponentUpdate();	
	}

	void MessageHandler(ComponentMessage &msg) { ComponentMessageHandler(msg); };


	virtual void ComponentUpdate() {};
	virtual void ComponentMessageHandler(ComponentMessage &msg) {};

protected:
	void DrawSprite(sf::Sprite * sprite, float x, float y, float  angle) {
		sprite->setPosition(BOX_2_SF(x), BOX_2_SF(y));
		
		sprite->setRotation(RAD_2_DEGREES(angle));
		this->window->draw(*sprite);
	}

	sf::RenderWindow *window;
	Item * item;
};
