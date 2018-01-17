#pragma once
#include "BloxFW/BloxFW.h"
#include "Types.h"


class Component;
class EntityManager;


class Entity : public bx::Box
{
	
public:
	Entity(std::string name) : Box(name) {}
	virtual ~Entity() {};

	virtual void Update();

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
  EntityManager * GetManager();

	bool IsEnabled();
	void Enable(bool state);

	std::string PrintEntity();

private:
	bool enabled = true;
};


