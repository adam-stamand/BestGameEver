#pragma once
#include <SFML/Graphics.hpp>
#include "Entity/Component.h"
#include "Entity/EntityBase.h"
#include <assert.h>

class Entity : public EntityBase
{

private:
	typedef std::vector<Component *> ComponentVec;
	ComponentVec components;

public:
	Entity(ComponentVec components, float x, float y)
	{
		this->components = components;
		this->x_pos = x;
		this->y_pos = y;
	};

	~Entity() {};


	void SendMessage(EntityMessage * msg) {

		for (int i = 0; i < components.size(); i++) {
			if (msg->comp_ID == components.at(i)->ID) {
				components.at(i)->MessageHandler(msg->comp_msg);
				return;
			}
		}
		assert(0);
	}

	void Update(sf::RenderWindow &window) {
		for (int i = 0; i < components.size(); i++) {
			components.at(i)->Update(*this, window);
		}
	}

};

