#pragma once
#include "Entity/Component.h"

class ControlsComponent : public Component
{
public:
	ControlsComponent() { this->ID = CONTROLS; };
	~ControlsComponent() {};

};

