#include "EntityManager.h"

// Find better way to iterate through array of entities; In Update function


Entity* EntityManager::entities[MAX_ENTITIES] = {0}; 




Entity * EntityManager::GetEntity(uint32_t id) {
	return entities[id];
}

void EntityManager::RegisterEntity(Entity *entity) {
	assert(entity != NULL);

	DebugManager::LogActivity("Registered" + entity->PrintEntity());
	entities[entity->GetID()] = entity;
}


void EntityManager::DeRegisterEntity(uint32_t id) {
	delete(entities[id]);
	DebugManager::LogActivity("Deregistered" + entities[id]->PrintEntity());
	entities[id] = NULL;
}


void EntityManager::EnableEntity(uint32_t id) {
	if (entities[id] == NULL) {
		DebugManager::LogError("Enabling entity failed; Entity " + std::to_string(id) + " does not exist");
		assert(0);
	}
	DebugManager::LogActivity("Enabled" + entities[id]->PrintEntity());
	entities[id]->Enable(true);
}


void EntityManager::DisableEntity(uint32_t id) {
	if (entities[id] == NULL) {
		DebugManager::LogError("Disabling entity failed; Entity " + std::to_string(id) + " does not exist");
		assert(0);
	}
	DebugManager::LogActivity("Disabled" + entities[id]->PrintEntity());
	entities[id]->Enable(false);
}


void EntityManager::EnableComponent(uint32_t id, ComponentID compID) {
	if (entities[id] == NULL) {
		DebugManager::LogError("Enabling entity failed; Entity " + std::to_string(id) + " does not exist");
		assert(0);
	}
	entities[id]->EnableComponent(compID);
}


void EntityManager::DisableComponent(uint32_t id, ComponentID compID) {
	if (entities[id] == NULL) {
		DebugManager::LogError("Enabling entity failed; Entity " + std::to_string(id) + " does not exist");
		assert(0);
	}
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


void EntityManager::SendMessage(uint32_t id, ComponentMessage &msg) {
	
	if (entities[id] == NULL) {
		DebugManager::LogError("Sending entity message failed; Entity " + std::to_string(id) + " does not exist");
		assert(0);
	}
	if (!entities[id]->IsEnabled()) {
		DebugManager::LogError("Sending entity message failed; Entity Disabled" + entities[id]->PrintEntity());
		assert(0);
	}
	entities[id]->SendMessage(msg);
}




