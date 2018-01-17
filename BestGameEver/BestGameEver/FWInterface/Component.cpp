#include "FWInterface/EntityManager.h"
#include <assert.h>
#include <array>
#include <string>
#include <iostream>
#include "Types.h"
#include "FWInterface/Component.h"
#include "FWInterface/Entity.h"



Entity * Component::GetEntity() {
  return static_cast<Entity*>(this->GetBox());
}


EntityManager * Component::GetManager() {
  return static_cast<EntityManager*>(this->GetManagerBox());
}


