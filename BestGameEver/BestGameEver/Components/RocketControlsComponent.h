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

	void RocketControlsComponent::FireGun(Entity &entity);
	void RocketControlsComponent::MoveForward(Entity &entity);
	void RocketControlsComponent::RotateClockwise(Entity &entity);
	void RocketControlsComponent::RotateCounterClockwise(Entity &entity);
};

