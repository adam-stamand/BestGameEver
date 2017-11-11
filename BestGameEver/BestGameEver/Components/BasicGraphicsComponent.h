#pragma once
#include "Entity/GraphicsComponentBase.h"

class BasicGraphicsComponent : public GraphicsComponentBase
{
public:
	BasicGraphicsComponent(sf::RenderWindow *window, sf::Sprite *sprite) : GraphicsComponentBase(window, sprite) {};
	~BasicGraphicsComponent() {};

	void MessageHandler(ComponentMessage *msg) {
		switch (msg->func_ID) {

		}
	};
};

