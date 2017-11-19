#include "EntityManager.h"


EntityBase* EntityManager::entities[MAX_ENTITIES] = {0};

void EntityManager::RegisterEntity(EntityBase *entity) {
	entities[entity->id] = entity;
}

void EntityManager::DeRegisterEntity(int id) {
	entities[id] = NULL;
}


void EntityManager::Update(sf::RenderWindow &window) {
	
	for (int i = 0; i < MAX_ENTITIES; i++) {
		if (entities[i] != NULL) {
			entities[i]->Update();
		}
	}
	
}




