#pragma once

#include "Component/GraphicsComponentBase.h"


class BasicGraphicsComponent : public GraphicsComponentBase
{
public:
	BasicGraphicsComponent(sf::RenderWindow *window, Item * item) : GraphicsComponentBase(window, item) {};
	~BasicGraphicsComponent() {};
};

