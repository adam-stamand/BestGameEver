#pragma once

#include "Component/GraphicsComponentBase.h"


class BasicGraphicsComponent : public GraphicsComponentBase
{
public:
	BasicGraphicsComponent(sf::RenderWindow *window, Item * item) : GraphicsComponentBase(window, item) {};
	BasicGraphicsComponent(sf::RenderWindow *window) : GraphicsComponentBase(window, NULL) {};

	void Init(Item * item) {
		this->item = item;
	}

	~BasicGraphicsComponent() {};
};

