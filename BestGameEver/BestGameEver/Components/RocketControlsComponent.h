#pragma once
#include "Entity/ControlsComponentBase.h"
#include "Level/EntityManager.h"
#include "Entity/Message.h"
#include "Box2D/Box2D.h"

class RocketControlsComponent : public ControlsComponentBase<RocketControlsComponent>
{
public:
	RocketControlsComponent();
	~RocketControlsComponent() {}


	void MessageHandler(ComponentMessage &msg) {
		switch (msg.funcID) {
		}
	};

	void RocketControlsComponent::FireGun(EntityInterface &entity);
	void RocketControlsComponent::MoveForward(EntityInterface &entity);
	void RocketControlsComponent::RotateClockwise(EntityInterface &entity);
	void RocketControlsComponent::RotateCounterClockwise(EntityInterface &entity);
};

