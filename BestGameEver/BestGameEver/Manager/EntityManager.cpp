#include "EntityManager.h"

// Find better way to iterate through array of entities; In Update function


Entity* EntityManager::entities[MAX_ENTITIES] = {0}; 


void EntityManager::RegisterEntity(Entity *entity) {
	assert(entity != NULL);
	entities[entity->GetID()] = entity;
}


void EntityManager::DeRegisterEntity(uint32_t id) {
	delete(entities[id]);
	entities[id] = NULL;
}


void EntityManager::EnableEntity(uint32_t id) {
	assert(entities[id] != NULL);
	entities[id]->Enable(true);
}


void EntityManager::DisableEntity(uint32_t id) {
	assert(entities[id] != NULL);
	entities[id]->Enable(false);
}


void EntityManager::EnableComponent(uint32_t id, ComponentID compID) {
	assert(entities[id] != NULL);
	entities[id]->EnableComponent(compID);
}


void EntityManager::DisableComponent(uint32_t id, ComponentID compID) {
	assert(entities[id] != NULL);
	entities[id]->DisableComponent(compID);
}



void EntityManager::Update(sf::RenderWindow &window) {
	
	for (int i = 0; i < MAX_ENTITIES; i++) {
		if (entities[i] != NULL) {
			if (entities[i]->IsEnabled()) {
				entities[i]->Update();
			}
		}
	}	
}


void EntityManager::SendMessage(uint32_t entityID, ComponentMessage &msg) {
	assert(entities[entityID]->IsEnabled());
	entities[entityID]->SendMessage(msg);
}




