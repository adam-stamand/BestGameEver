#pragma once
#include "BaseComponents/SFMLControls/SFMLControlsComponent.h"

class BasicControlsComponent : public SFMLControlsComponent<BasicControlsComponent>
{
public:
	BasicControlsComponent(std::string name);
	~BasicControlsComponent() {};

	void MoveForward();
  void MoveBackward();
  void RotateLeft();
  void RotateRight();

};
