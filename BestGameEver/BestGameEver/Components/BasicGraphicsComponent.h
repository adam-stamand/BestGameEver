#pragma once
#include "Entity/GraphicsComponentBase.h"

class BasicGraphicsComponent : public GraphicsComponentBase
{
public:
	BasicGraphicsComponent(sf::RenderWindow *window, std::vector<sf::Sprite*> sprites) : GraphicsComponentBase(window, sprites) {};
	~BasicGraphicsComponent() {};

	void MessageHandler(ComponentMessage &msg) {
		switch (msg.funcID) {

		}
	};
};

