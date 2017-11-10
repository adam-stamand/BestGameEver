#pragma once
#include "Entity/Component.h"

class GraphicsComponent : public Component
{

public:
	GraphicsComponent(char ch);

	~GraphicsComponent() {};


protected:
	sf::Text text;
	static sf::Font font;
};
