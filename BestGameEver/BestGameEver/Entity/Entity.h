#pragma once
#include "Entity/ComponentBase.h"
#include "Entity/EntityBase.h"
#include <assert.h>

typedef std::vector<ComponentBase *> ComponentVec;



class Entity : public EntityBase
{

private:
	ComponentVec components;

public:
	Entity(ComponentVec components, float x, float y, float angle)
	{
		this->components = components;
		this->x_pos = x;
		this->y_pos = y;
		this->angle = angle;
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

	void Update() {
		for (int i = 0; i < components.size(); i++) {
			components.at(i)->Update(*this);
		}
	}

};

