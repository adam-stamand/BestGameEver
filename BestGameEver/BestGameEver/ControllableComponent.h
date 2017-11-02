#pragma once
class ControllableComponent
{
public:
	ControllableComponent();
	virtual ~ControllableComponent() {};

	virtual void Update() = 0;
};

