#pragma once
#include "Entity/Component.h"

class GraphicsComponent : public Component
{

public:
	GraphicsComponent(char ch);
	~GraphicsComponent() {};

	virtual void Update(EntityBase &entity, sf::RenderWindow &window) {
		this->text.setPosition(entity.x_pos, entity.y_pos);
		puts("drawing");
		window.draw(this->text);
	};

protected:
	sf::Text text;
	static sf::Font font;
	sf::Sprite sprite;
};
