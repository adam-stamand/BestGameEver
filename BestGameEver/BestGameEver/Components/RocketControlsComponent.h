#pragma once
#include "Entity/ControlsComponentBase.h"
#include "Box2D/Box2D.h"

class RocketControlsComponent : public ControlsComponentBase<RocketControlsComponent>
{
public:
	RocketControlsComponent();
	~RocketControlsComponent() {};


	void MessageHandler(ComponentMessage *msg) {
		switch (msg->func_ID) {
		}
	};



	void RocketControlsComponent::MoveForward(EntityBase &entity);
	void RocketControlsComponent::RotateClockwise(EntityBase &entity);
	void RocketControlsComponent::RotateCounterClockwise(EntityBase &entity);

};

