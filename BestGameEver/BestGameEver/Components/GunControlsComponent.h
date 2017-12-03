#pragma once

#include "Entity/ControlsComponentBase.h"
#include "Level/EntityManager.h"
#include "Entity/Message.h"
#include "Box2D/Box2D.h"


class GunControlsComponent : public ControlsComponentBase<GunControlsComponent>
{
public:
	GunControlsComponent();
	~GunControlsComponent();

	void MessageHandler(ComponentMessage &msg) {
		switch (msg.funcID) {
		}
	};

	void GunControlsComponent::FireGun(sf::Event &evnt, EntityInterface &entity);


};

