#pragma once
#include "FWInterface/FWInterface.h"
#include "Factory/EntityFactory/UserEntity.h"

class EntityFactory
{

public:
  template <typename T>
  static Entity * CreateEntity(std::string name);
};


template <typename T>
Entity * EntityFactory::CreateEntity(std::string name) {
  T ent_t;
  Entity * ent = new Entity(name);
  ent->AddComponents(ent_t.components);
  return ent;
}





