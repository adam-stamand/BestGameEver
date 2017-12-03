#pragma once
#include "Entity/GraphicsComponentBase.h"


class BasicGraphicsComponent : public GraphicsComponentBase
{
public:
	BasicGraphicsComponent(sf::RenderWindow *window, std::vector<ItemFixture*> itemFixtures) : GraphicsComponentBase(window, itemFixtures) {};
	~BasicGraphicsComponent() {};

	void MessageHandler(ComponentMessage &msg) {
		switch (msg.funcID) {

		}
	};
};

