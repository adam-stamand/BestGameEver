#pragma once

#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"
#include "Entity/Entity.h"


class ContactManager : public b2ContactListener
{
public:
	enum ContactType {
		CONTACT_BEGIN,
		CONTACT_END

	};

	ContactManager() {};
	~ContactManager() {};

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);

	void GetIDs(b2Contact* contact, uint32_t &idA, uint32_t &idB);
	void SearchContact(uint32_t idA, uint32_t idB, ContactType type);
	bool CheckContact(uint32_t idA, uint32_t idB, std::vector<uint32_t> idVec);
	void RegisterContact(Entity *entity);
	void RegisterFilter(std::vector<uint32_t> filter);

private:
	std::vector<Entity*> entities;
	std::vector<std::vector<uint32_t>> collisionFilters;
};

