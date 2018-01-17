#include "FWInterface/EntityManager.h"
#include <assert.h>
#include <array>
#include <iostream>
#include <string.h>

#include "FWInterface/Component.h"
#include "Entity.h"


std::string Entity::PrintEntity() {
	return (" - " + this->GetName() + "(id:" + std::to_string(this->GetID()) + ")");
}

EntityManager * Entity::GetManager() {
  return (EntityManager*)this->GetManagerBox();
}

bool Entity::IsEnabled() {
	return this->enabled;
}


void Entity::Enable(bool state) {
	this->enabled = state;
}


int Entity::AddComponents(std::vector<Component*> components) {
  std::vector<bx::Block*> temp;
  for (int i = 0; i < components.size(); i++) {
    temp.push_back(components.at(i));
  }
  return this->AddBlocks(temp);
};

void Entity::Update() {
	for (auto iter = comps_begin(); iter != comps_end(); iter++) {
    Component * comp = GetComponent(iter->second);
    if (comp->IsEnabled()) {
      comp->Update();
    }
	}
}


int Entity::AddEntity(Entity* entity) {
  return this->AddBox(entity);
};


Entity * Entity::GetEntity() {
  return static_cast<Entity*>(GetBox());
}

