#pragma once

#include <math.h>
#include <string.h>

#include "Component/ComponentBase.h"
#include "Factory/Item.h"
#include "Globals/Globals.h"


class GraphicsComponentBase : public ComponentBase
{
public:
	GraphicsComponentBase(sf::RenderWindow *window, Item * item);
	~GraphicsComponentBase() {};

	void Update();
	void MessageHandler(ComponentMessage &msg);
	virtual void ComponentUpdate() {};
	virtual void ComponentMessageHandler(ComponentMessage &msg) {};

protected:
	void DrawSprite(sf::Sprite * sprite, float x, float y, float  angle);
	sf::RenderWindow *window;
	Item * item;
};
