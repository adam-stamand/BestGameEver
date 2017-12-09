#include "Entity/Entity.h"



void Entity::Init(ComponentVec comps) {
	for (int i = 0; i < comps.size(); i++) {
		comps.at(i)->SetEntityID(this->GetID());
		components[comps.at(i)->GetComponentID()] = comps.at(i);
	}
}


void Entity::AddComponent(ComponentBase * component) {
	this->components[component->GetComponentID()] = component;
}


uint32_t Entity::GetID() {
	return this->id;
}


bool Entity::IsEnabled() {
	return this->enabled;
}


void Entity::Enable(bool state) {
	this->enabled = state;
}


void Entity::RemoveComponent(ComponentID id) {
	delete(components[id]);
	components[id] = NULL;
}


void Entity::EnableComponent(ComponentID id) {
	assert(this->components[id] != NULL);
	this->components[id]->Enable(true);
}


void Entity::DisableComponent(ComponentID id) {
	assert(this->components[id] != NULL);
	this->components[id]->Enable(false);
}


void Entity::SendMessage(ComponentMessage &msg) {
	if (this->components[msg.compID] == NULL) {
		printf("Entity %d sending message to component %d\n",this->id,  msg.compID);
		assert(0);

	}
	components[msg.compID]->MessageHandler(msg);
	
}


void Entity::Update() {
	for (int i = 0; i < components.size(); i++) {
		if (components[i] != NULL) {
			if (components[i]->IsEnabled()) {
				components[i]->Update();
			}
		}
	}
}

