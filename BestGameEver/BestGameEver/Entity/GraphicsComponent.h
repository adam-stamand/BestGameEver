#pragma once
#include "Entity/Component.h"

class GraphicsComponent : public Component
{

public:
	GraphicsComponent(char ch);
	~GraphicsComponent() {};

	virtual void Update(EntityBase &entity, sf::RenderWindow &window) {
		this->sprite.setPosition(entity.x_pos, entity.y_pos);
		window.draw(this->sprite);
	};

protected:
	sf::Text text;
	static sf::Font font;
	sf::Texture texture;
	sf::Sprite sprite;
};
