#pragma once

#include <SFML/Graphics.hpp>
#include <assert.h>
#include "Entity/Entity.h"


#define MAX_ENTITIES 1024

class EntityManager
{
public:
	EntityManager() {};
	~EntityManager() {};

	static void EntityManager::RegisterEntity(Entity *entity);
	static void EntityManager::DeRegisterEntity(uint32_t id);
	static void EntityManager::EnableEntity(uint32_t id);
	static void EntityManager::DisableEntity(uint32_t id);

	static void EntityManager::EnableComponent(uint32_t id, ComponentID compID);
	static void EntityManager::DisableComponent(uint32_t id, ComponentID compID);
	static void EntityManager::Update(sf::RenderWindow &window);
	static void EntityManager::SendMessage(uint32_t entityID, ComponentMessage &msg);
	
private:
	static Entity* entities[MAX_ENTITIES];
};


