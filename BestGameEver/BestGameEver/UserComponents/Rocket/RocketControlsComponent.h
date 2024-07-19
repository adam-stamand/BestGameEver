#pragma once
#include "BaseComponents/SFMLControls/SFMLControlsComponent.h"

class RocketControlsComponent : public SFMLControlsComponent<RocketControlsComponent>
{
public:
	RocketControlsComponent(std::string name);
	~RocketControlsComponent() {};

	void MoveForward();
  void RotateLeft();
  void RotateRight();

};
