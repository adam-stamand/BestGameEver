#pragma once
#include "Entity/ComponentBase.h"
#include <string.h>

#define RAD_2_DEGREES(x) (x * 57.295779513)

class GraphicsComponentBase : public ComponentBase
{

public:
	GraphicsComponentBase(std::string str, sf::RenderWindow *window) {
		this->window = window;
		texture.loadFromFile(str);
		sprite.setTexture(texture);
		//this->sprite.setColor(sf::Color(0, 55, 05, 128));
		//this->sprite.setPosition(200.f, 100.f);
		//this->sprite.setRotation(30.f);
		//sf::FloatRect rect = sprite.getGlobalBounds();
		//this->sprite.setOrigin(, 0);
		this->sprite.setScale(.25f, 0.25f);
		this->ID = GRAPHICS;
	};

	~GraphicsComponentBase() {};

	virtual void Update(EntityBase &entity) {
		this->sprite.setPosition(entity.x_pos, entity.y_pos);
		this->sprite.setRotation(RAD_2_DEGREES(entity.angle));
		this->window->draw(this->sprite);
	};

protected:
	sf::RenderWindow *window;
	sf::Texture texture;
	sf::Sprite sprite;
};
