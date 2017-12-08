#pragma once

#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"
#include "Entity/Entity.h"


class ContactManager : public b2ContactListener
{
public:
	ContactManager() {};
	~ContactManager() {};

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);

	void GetIDs(b2Contact* contact, uint32_t &idA, uint32_t &idB);
	Entity * SearchContact(b2Contact* contact, uint32_t idA, uint32_t idB);
	bool CheckContact(uint32_t idA, uint32_t idB, std::vector<uint32_t> testIDs);
	void RegisterContact(Entity *entity);
	void RegisterFilter(std::vector<uint32_t> filter);

private:
	std::vector<Entity*> entities;
	std::vector<std::vector<uint32_t>> collisionFilters;
};

