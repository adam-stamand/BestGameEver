#pragma once
#include "Entity/ControlsComponent.h"
#include "Entity/ControlsBase.h"


class MainControlsComponent : public ControlsBase<MainControlsComponent>, public ControlsComponent
{
public:
	MainControlsComponent();
	~MainControlsComponent();


	void Update(EntityBase &entity, sf::RenderWindow &window);
	void MessageHandler(ComponentMessage *msg) {
		switch (msg->func_ID) {
		}
	};	

	void MoveUp(EntityBase &entity);
	void MoveDown(EntityBase &entity);
	void MoveLeft(EntityBase &entity);
	void MoveRight(EntityBase &entity);

private:

};
