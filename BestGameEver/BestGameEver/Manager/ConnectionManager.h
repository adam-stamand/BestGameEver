#pragma once

#include "Box2D/Box2D.h"
#include "Entity/Entity.h"
#include <vector>
#include <map>


class ConnectionManager : public b2ContactListener
{

public:
	enum ContactType {
		CONTACT_BEGIN,
		CONTACT_END
	};

	static struct EntityConnection{
		EntityID primaryContact;
		std::vector<EntityID> secondaryContacts;
	};

	static struct ContactConnection {
		EntityConnection connection;
		EntityID contact = 0;
		bool listenContact = false;
	};

	ConnectionManager() {};
	~ConnectionManager() {};

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact) ;
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) ;
	
	static void GetIDs(b2Contact* contact, EntityID &idA, EntityID &idB);
	static void SearchContact(EntityID idA, EntityID idB, ContactType type);
	static EntityID CheckContact(EntityID idA, EntityID idB, EntityConnection * collision);

	static void RegisterConnection(EntityID primaryContact, std::vector<EntityID> secondaryContacts, std::string name, bool listenContact = false);
	static void RegisterCollisionFilter(EntityID primaryContact, std::vector<EntityID> secondaryContacts);
	static void ConnectionManager::GetConnection(std::string str, EntityID &primary, std::vector<EntityID> &secondary);
	static bool ConnectionManager::GetContactConnection(std::string str, EntityID &primary, EntityID &secondary);
	static std::map<std::string, ContactConnection*> connectionMap;
	static std::vector<EntityConnection*> collisionFilters;
private:

	};

