#pragma once
#include "Entity/ComponentBase.h"
#include "Entity/Message.h"
#include <string.h>
#include "Factory/Item.h"

#include <math.h>
class GraphicsComponentBase : public ComponentBase
{

public:
	GraphicsComponentBase(sf::RenderWindow *window, std::vector<ItemFixture*> itemFixtures) : ComponentBase(GRAPHICS) {
		this->itemFixtures = itemFixtures;
		this->window = window;
	};

	~GraphicsComponentBase() {};

	virtual void Update(EntityInterface &entity) {
		ComponentMessage::Transform trans;
		ComponentMessage comp_msg(PHYSICS, ComponentMessage::GET_TRANS, &trans); // figure out for multiple fixtures
		entity.SendMessage(comp_msg);
		for (int i = 0; i < itemFixtures.size(); i++) {
			b2Vec2 offset(0,0);

			if (this->itemFixtures.at(i)->center.x || this->itemFixtures.at(i)->center.y) {
				offset.x = cos(trans.angle) * this->itemFixtures.at(i)->center.x - sin(trans.angle) * this->itemFixtures.at(i)->center.y;
				offset.y = sin(trans.angle) * this->itemFixtures.at(i)->center.x + cos(trans.angle) * this->itemFixtures.at(i)->center.y;
			}
			
			this->itemFixtures.at(i)->sprite->setPosition(BOX_2_SF(trans.xPos + offset.x), BOX_2_SF(trans.yPos + offset.y));
			this->itemFixtures.at(i)->sprite->setRotation(RAD_2_DEGREES(trans.angle) + itemFixtures.at(i)->angle);
			
			this->window->draw(*(this->itemFixtures.at(i)->sprite));
		}
		
	};

protected:
	sf::RenderWindow *window;
	std::vector<ItemFixture*> itemFixtures;
};
