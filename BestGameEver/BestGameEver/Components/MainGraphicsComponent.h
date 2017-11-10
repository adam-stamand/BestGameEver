#pragma once

#include "Entity/GraphicsComponent.h"

class MainGraphicsComponent : public GraphicsComponent
{
public:
	MainGraphicsComponent(char ch) : GraphicsComponent(ch) {};
	~MainGraphicsComponent() {};




	void MessageHandler(ComponentMessage *msg) {
		switch (msg->func_ID) {

		}
	};


};

