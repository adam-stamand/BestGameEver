#pragma once
#include "Entity/ComponentBase.h"
#include <string.h>

#define RAD_2_DEGREES(x) (x * 57.295779513)

class GraphicsComponentBase : public ComponentBase
{

public:
	GraphicsComponentBase(sf::RenderWindow *window, sf::Sprite *sprite) {
		this->sprite = sprite;
		this->window = window;
		this->ID = GRAPHICS;
	};

	~GraphicsComponentBase() {};

	virtual void Update(EntityBase &entity) {
		this->sprite->setPosition(entity.x_pos, entity.y_pos);
		this->sprite->setRotation(RAD_2_DEGREES(entity.angle));
		this->window->draw(*(this->sprite));
	};

protected:
	sf::RenderWindow *window;
	sf::Sprite *sprite;
};
