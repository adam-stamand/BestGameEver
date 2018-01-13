#pragma once
#include "Entity/ControlsComponentBase.h"
#include "Entity/Entity.h"
#include "Box2D/Box2D.h"

class BasicControlsComponent : public ControlsComponentBase<BasicControlsComponent>
{
public:
	BasicControlsComponent();
	~BasicControlsComponent() {};

	void MessageHandler(ComponentMessage *msg) {
		switch (msg->funcID) {
		}
	};	

	void Teleport(sf::Event &evnt_p, Entity &entity);
	void MoveUp(Entity &entity);
	void MoveDown(Entity &entity);
	void MoveLeft(Entity &entity);
	void MoveRight(Entity &entity);

};
