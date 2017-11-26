#pragma once
#include "Entity/ControlsComponentBase.h"
#include "Level/EntityManager.h"
#include "Entity/Message.h"
#include "Box2D/Box2D.h"



class CharacterControlsComponent : public ControlsComponentBase<CharacterControlsComponent>
{
public:
	CharacterControlsComponent();
	~CharacterControlsComponent();

	void MessageHandler(ComponentMessage &msg) {
		switch (msg.funcID) {
		}
	};

	void FireGun(Entity &entity);
	void MoveLeft(Entity &entity);
	void MoveRight(Entity &entity);
};

