#include "EntityManager.h"


Entity* EntityManager::entities[MAX_ENTITIES] = {0}; // amke sure all elements go to 0


void EntityManager::RegisterEntity(Entity *entity) {
	entities[entity->id] = entity;
}


void EntityManager::DeRegisterEntity(int id) {
	delete(entities[id]);
	entities[id] = NULL; // check if delete leaves null already
}


void EntityManager::EnableEntity(int id) {
	entities[id]->enabled = true;
}


void EntityManager::DisableEntity(int id) {
	entities[id]->enabled = false;
}


void EntityManager::Update(sf::RenderWindow &window) {
	
	for (int i = 0; i < MAX_ENTITIES; i++) {
		if (entities[i] != NULL) {
			if (entities[i]->enabled) {
				entities[i]->Update();
			}
		}
	}	
}


void EntityManager::SendMessage(EntityMessage &msg) {
	if (entities[msg.entityID]->enabled) {
		entities[msg.entityID]->SendMessage(msg);
	}
	else {
		assert(0);
	}
}




