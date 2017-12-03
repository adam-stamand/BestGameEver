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

	void FireGun(EntityInterface &entity);
	void MoveLeft(EntityInterface &entity);
	void MoveRight(EntityInterface &entity);
};

