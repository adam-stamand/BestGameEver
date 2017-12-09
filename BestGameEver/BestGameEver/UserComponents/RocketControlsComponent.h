#pragma once

#include "Component/ControlsComponentBase.h"
#include "Manager/EntityManager.h"



class RocketControlsComponent : public ControlsComponentBase<RocketControlsComponent>
{
public:
	RocketControlsComponent();
	~RocketControlsComponent() {}

	void RocketControlsComponent::MoveForward();
	void RocketControlsComponent::RotateClockwise();
	void RocketControlsComponent::RotateCounterClockwise();
};

