#pragma once
#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"
#include "Factory/UserEntityType.h"
#include "Manager/EntityManager.h"
#include "Factory/EntityFactoryInterface.h"


class EntityFactory : public EntityFactoryInterface
{
public:
	EntityFactory();
	~EntityFactory();


	uint32_t CreateEntity(FactoryCatalogue num) {
		EntityType * userType = NULL;
		switch (num) {
		case GRENADE_ENT: {
			userType = new GrenadeEntity;
			break;
		}
		}
		return _CreateEntity(*userType);
	}


	uint32_t _CreateEntity(EntityType &entityType);
};