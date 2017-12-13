#pragma once
#include "Factory/EntityType.h"
#include "Factory/Factory.h"
#include "Globals/Globals.h"
#include "UserComponents/UserComponents.h"



class GrenadeEntity : public EntityType {
public:
	GrenadeEntity() {
		std::vector<Part*> wheel2Parts{
			Factory::CreatePart<Tire>(b2Vec2(0,0), b2Vec2(1,1))
		};
		Item * item = new Item;
		item = Factory::CreateItem(wheel2Parts, DYNAMIC_BODY);
		item->body->SetTransform(b2Vec2(SF_2_BOX(600), SF_2_BOX(500)), 0);

		this->components = {
			new GrenadePhysicsComponent2(60 ,item),
			new BasicGraphicsComponent(&Globals::window, item)
		};
	}
};