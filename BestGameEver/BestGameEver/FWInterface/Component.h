#pragma once
#include "BloxFW/BloxFW.h"

class Entity;
class EntityManager;

class Component : public bx::Block
{

public:
	Component(std::string name) : bx::Block(name) {};
	virtual ~Component() {};

	virtual void Update() = 0;

  Entity * GetEntity();
  EntityManager * GetManager();

	bool IsEnabled() { return this->m_enabled; };
	void Enable(bool state) { this->m_enabled = state; };

private:
	bool m_enabled = true;
};

