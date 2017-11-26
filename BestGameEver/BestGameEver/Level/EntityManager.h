#pragma once
#include <SFML/Graphics.hpp>
#include "Entity/Entity.h"
#include <assert.h>


#define MAX_ENTITIES 1024

class EntityManager
{
public:
	EntityManager() {};
	~EntityManager() {};

	static void EntityManager::RegisterEntity(Entity *entity);
	static void EntityManager::DeRegisterEntity(int id);
	static void EntityManager::EnableEntity(int id);
	static void EntityManager::DisableEntity(int id);
	static void EntityManager::Update(sf::RenderWindow &window);
	static void EntityManager::SendMessage(EntityMessage &msg);
	
private:
	static Entity* entities[MAX_ENTITIES];
};


