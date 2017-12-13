#include "Factory/EntityFactory.h"



EntityFactory::EntityFactory()
{
}


EntityFactory::~EntityFactory()
{
}

uint32_t EntityFactory::_CreateEntity(EntityType &userEntityType) {
	Entity *entity = new Entity;
	std::vector<Part*> borderParts;
	entity->AddComponent(userEntityType.components);
	EntityManager::RegisterEntity(entity);
	return entity->GetID();
}

