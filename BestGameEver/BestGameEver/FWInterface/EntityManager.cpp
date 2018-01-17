#include "EntityManager.h"
#include <assert.h>
#include <array>
#include <string>
#include <iostream>

#include "FWInterface/Component.h"
#include "FWInterface/Entity.h"




void EntityManager::Update() {
  Entity * ent;
  for (auto iter = managedEnts_begin(); iter != managedEnts_end(); iter++) {
    ent = GetManagedEntity(iter->second);
    if (iter->second == 0) continue;
    if (ent->IsEnabled()) {
      ent->Update();
    }
  }
}


int EntityManager::AddComponents(std::vector<Component*> components) {
  std::vector<bx::Block*> temp;
  for (int i = 0; i < components.size(); i++) {
    temp.push_back(components.at(i));
  }
  return this->AddBlocks(temp);
};


int EntityManager::AddEntity(Entity* entity) {
  return this->AddBox(entity);
};


Entity * EntityManager::GetEntity() {
  return static_cast<Entity*>(GetBox());
}