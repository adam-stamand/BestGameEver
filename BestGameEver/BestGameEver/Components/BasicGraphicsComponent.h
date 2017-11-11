#pragma once
#include "Entity/GraphicsComponentBase.h"

class BasicGraphicsComponent : public GraphicsComponentBase
{
public:
	BasicGraphicsComponent(std::string str, sf::RenderWindow *window) : GraphicsComponentBase(str, window) {};
	~BasicGraphicsComponent() {};

	void MessageHandler(ComponentMessage *msg) {
		switch (msg->func_ID) {

		}
	};
};

