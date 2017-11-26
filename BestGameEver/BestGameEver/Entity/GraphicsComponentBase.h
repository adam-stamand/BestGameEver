#pragma once
#include "Entity/ComponentBase.h"
#include "Entity/Message.h"
#include <string.h>



class GraphicsComponentBase : public ComponentBase
{

public:
	GraphicsComponentBase(sf::RenderWindow *window, std::vector<sf::Sprite*> sprites) : ComponentBase(GRAPHICS) {
		this->sprites = sprites;
		this->window = window;
	};

	~GraphicsComponentBase() {};

	virtual void Update(EntityBase &entity) {
		
		ComponentMessage::Transform trans;
		ComponentMessage comp_msg(PHYSICS, ComponentMessage::GET_TRANS, &trans); // figure out for multiple fixtures
		entity.SendMessage(comp_msg);
		for (int i = 0; i < sprites.size(); i++) {
			this->sprites.at(i)->setPosition(BOX_2_SF(trans.xPos), BOX_2_SF(trans.yPos));
			this->sprites.at(i)->setRotation(RAD_2_DEGREES(trans.angle));
			this->window->draw(*(this->sprites.at(i)));
		}
		
	};

protected:
	sf::RenderWindow *window;
	std::vector<sf::Sprite*> sprites;
};
