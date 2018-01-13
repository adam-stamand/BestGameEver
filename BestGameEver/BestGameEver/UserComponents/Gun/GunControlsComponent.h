#pragma once

#include "Component/ControlsComponentBase.h"
#include "Manager/EntityManager.h"




class GunControlsComponent : public ControlsComponentBase<GunControlsComponent>
{
public:
	GunControlsComponent();
	~GunControlsComponent() {};

	void GunControlsComponent::FireGun(sf::Event &evnt);
};

