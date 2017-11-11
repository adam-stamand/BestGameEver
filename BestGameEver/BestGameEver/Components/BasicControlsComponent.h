#pragma once
#include "Entity/ControlsComponentBase.h"
#include "Box2D/Box2D.h"

class BasicControlsComponent : public ControlsComponentBase<BasicControlsComponent>
{
public:
	BasicControlsComponent();
	~BasicControlsComponent() {};

	void MessageHandler(ComponentMessage *msg) {
		switch (msg->func_ID) {
		}
	};	

	void Teleport(sf::Event &evnt_p, EntityBase &entity);
	void MoveUp(EntityBase &entity);
	void MoveDown(EntityBase &entity);
	void MoveLeft(EntityBase &entity);
	void MoveRight(EntityBase &entity);

};
