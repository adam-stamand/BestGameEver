#pragma once
#include <SFML/Graphics.hpp>
#include "Entity/EntityBase.h"


#define MAX_ENTITIES 1024

class EntityManager
{
public:
	EntityManager() {};
	~EntityManager() {};

	static void EntityManager::RegisterEntity(EntityBase *entity);
	static void EntityManager::DeRegisterEntity(int id);
	static void EntityManager::Update(sf::RenderWindow &window);
	
	

private:
	static EntityBase* entities[MAX_ENTITIES];


};


