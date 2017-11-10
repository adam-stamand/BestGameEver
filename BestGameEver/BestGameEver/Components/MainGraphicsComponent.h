#pragma once

#include "Entity/GraphicsComponent.h"

class MainGraphicsComponent : public GraphicsComponent
{
public:
	MainGraphicsComponent(char ch) : GraphicsComponent(ch) {};
	~MainGraphicsComponent() {};

	void Update(EntityBase &entity, sf::RenderWindow &window) {
		this->text.setPosition(entity.x_pos, entity.y_pos);
		window.draw(this->text);
	};


	void MessageHandler(ComponentMessage *msg) {
		switch (msg->func_ID) {

		}
	};


};

