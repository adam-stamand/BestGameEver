#pragma once
#include "BloxFW/BloxFW.h"
#include "Types.h"

class Component;
class Entity;




//TODO Fix fucked up inheritance
class EntityManager : public bx::ManagerBox //TODO Fix interface so Entity functionality isnt duplicated
{
public:
	EntityManager(std::string name) : ManagerBox(name) {};
	~EntityManager() {};

  // Get any box or block manager by ManagerBox
  template <typename T>
  Entity * GetManagedEntity(T entIdentifier) {
    return (Entity*)this->GetManagedBox(entIdentifier);
  }

  template <typename T1, typename T2>
  Component * GetManagedComponent(T1 compIdentifier, T2 entIdentifier) {
    return this->GetManagedBlock(compIdentifier, entIdentifier);
  }


  // Add/Get/Remove Blocks
  int AddComponents(std::vector<Component*> components);

  template <typename T>
  Component * GetComponent(T compIdentifier) {
    return (Component*)this->GetBlock(compIdentifier);
  }

  template <typename T>
  int RemoveComponent(T compIdentifier) {
    return this->RemoveBlock(compIdentifier);
  }

  // Add/Get/Remove Blocks
  int AddEntity(Entity* entity);

  template <typename T>
  Entity * GetEntity(T entIdentifier) {
    return this->GetBox(entIdentifier);
  }

  template <typename T>
  int RemoveEntity(T entIdentifier) {
    return this->RemoveBox(entIdentifier);
  }

  // Iterators for contained boxes and blocks
  std::map<std::string, ComponentID>::const_iterator comps_begin() { return block_begin(); }
  std::map<std::string, ComponentID>::const_iterator comps_end() { return block_end(); }
  std::map<std::string, EntityID>::const_iterator ents_begin() { return box_begin(); }
  std::map<std::string, EntityID>::const_iterator ents_end() { return box_end(); }





  Entity * GetEntity();

  bool IsEnabled();
  void Enable(bool state);


  // Iterators for contained boxes and blocks
  std::map<std::string, EntityID>::const_iterator managedEnts_begin() { return managedBoxes_begin(); }
  std::map<std::string, EntityID>::const_iterator managedEnts_end() { return managedBoxes_end(); }

  
	void EntityManager::Update();

};


