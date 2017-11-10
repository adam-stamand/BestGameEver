#pragma once

#include "Entity/GraphicsComponent.h"

class MainGraphicsComponent : public GraphicsComponent
{
public:
	MainGraphicsComponent(std::string path) : GraphicsComponent(path) {};
	~MainGraphicsComponent() {};




	void MessageHandler(ComponentMessage *msg) {
		switch (msg->func_ID) {

		}
	};


};

