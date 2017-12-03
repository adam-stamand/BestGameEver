#include "Entity/Entity.h"



Entity::Entity(ComponentVec comps)  {
	for (int i = 0; i < comps.size(); i++) {
		components[comps[i]->id] = comps[i];
	}
}


void Entity::AddComponent(ComponentBase * component) {
	this->components[component->id] = component;
}


void Entity::RemoveComponent(ComponentID id) {
	delete(components[id]); //check if delete(NULL) is ok
	components[id] = NULL;
}


void Entity::EnableComponent(ComponentID id) {
	this->components[id]->enabled = true;
}


void Entity::DisableComponent(ComponentID id) {
	this->components[id]->enabled = false;
}


void Entity::SendMessage(ComponentMessage &msg) {
	if (components[msg.compID] != NULL) {
		components[msg.compID]->MessageHandler(msg);
	}
	else {
		puts("ERR: Component does not exist - Entity.cpp");
	}
}

void Entity::Update() {
	for (int i = 0; i < components.size(); i++) {
		if (components[i] != NULL) {
			if (components[i]->enabled) {
				components[i]->Update(*this);
			}
		}
	}
}

