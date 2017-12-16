#include "Entity/Entity.h"


std::string Entity::PrintEntity() {
	return (" - " + this->GetName() + "(id:" + std::to_string(this->GetID()) + ")");
}


void Entity::AddComponent(ComponentVec comps) {
	for (int i = 0; i < comps.size(); i++) {
		std::string temp = DebugManager::componentIDMap.find(comps[i]->GetComponentID())->second;
		DebugManager::LogActivity("Adding component " + temp + PrintEntity());
		comps[i]->SetEntityID(this->GetID());
		this->components[comps[i]->GetComponentID()] = comps[i];
	}
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
	std::string temp = DebugManager::componentIDMap.find(id)->second;
	DebugManager::LogActivity("Removed component " + temp + PrintEntity());
	delete(components[id]);
	components[id] = NULL;
}


void Entity::EnableComponent(ComponentID id) {
	std::string temp = DebugManager::componentIDMap.find(id)->second;
	if (this->components[id] == NULL) {
		DebugManager::LogError("Failed to enable component " + temp + "; Component does not exist" + PrintEntity());
		assert(0);
	}

	DebugManager::LogActivity("Enabling component " + temp + PrintEntity());
	this->components[id]->Enable(true);
}


void Entity::DisableComponent(ComponentID id) {
	std::string temp = DebugManager::componentIDMap.find(id)->second;
	if (this->components[id] == NULL) {
		DebugManager::LogError("Failed to disable component " + temp + "; Component does not exist" + PrintEntity());
		assert(0);
	}

	DebugManager::LogActivity("Disabling component " + temp + PrintEntity());
	this->components[id]->Enable(false);
}


void Entity::SendMessage(ComponentMessage &msg) {
	std::string temp = DebugManager::componentIDMap.find(msg.compID)->second;
	if (this->components[msg.compID] == NULL) {
		DebugManager::LogError("Failed to send message to component " + temp + "; Component does not exist" + PrintEntity());
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

