#include "Manager/ConnectionManager.h"

// Functions could probably be cleaned up
// Currently no way to Deregister collisionFilter or Contact

// consider using grouping for contatcts // example; all objects take damage when colliding with ground group


//another idea; you could puts contact handling in the user data of the body, so that
//contact manager just called that, no need to store references to entities; just an idea 


std::map<std::string, ConnectionManager::ContactConnection*> ConnectionManager::connectionMap;
std::vector<ConnectionManager::EntityConnection*> ConnectionManager::collisionFilters;

void ConnectionManager::BeginContact(b2Contact* contact) {
	EntityID idA, idB;
	ConnectionManager::GetIDs(contact, idA, idB);
	if (!idA || !idB) {
		return;
	}
	ConnectionManager::SearchContact(idA, idB, CONTACT_BEGIN);
}




void ConnectionManager::EndContact(b2Contact* contact) {
	EntityID idA, idB;
	ConnectionManager::GetIDs(contact, idA, idB);
	if (!idA || !idB) {
		return;
	}
	ConnectionManager::SearchContact(idA, idB, CONTACT_END);
}


void ConnectionManager::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
	EntityID idA, idB;
	this->GetIDs(contact, idA, idB);
	if (!idA || !idB) {
		return;
	}

	for (int i = 0; i < collisionFilters.size(); i++) {
		bool temp = ConnectionManager::CheckContact(idA, idB, collisionFilters[i]) ? true:false;
		if (temp) {
			contact->SetEnabled(false);	
		}
	}
}


void ConnectionManager::GetIDs(b2Contact* contact, EntityID &idA, EntityID &idB) {
	void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

	if (!(bodyUserDataA && bodyUserDataB)) {
		idA = 0; // 0 is an Invalid ID
		idB = 0;
		return;
	}

	Entity * entityA = static_cast<Entity*>(bodyUserDataA);
	Entity * entityB = static_cast<Entity*>(bodyUserDataB);

	idA = entityA->GetID();
	idB = entityB->GetID();
}


void ConnectionManager::SearchContact(EntityID idA, EntityID idB, ContactType type) {
	std::map<std::string, ContactConnection*>::iterator iter;

	for (iter = ConnectionManager::connectionMap.begin(); iter != ConnectionManager::connectionMap.end(); iter++) {
		ContactConnection * connection = iter->second;
		if (connection->listenContact) {
			EntityID tempID = CheckContact(idA, idB, &connection->connection);
			if (tempID) {
				if (type == CONTACT_END) {
					//ComponentMessage comp_msg(CONNECTION, ComponentMessage::CONTACT_END, (void*)&temp);
					//entities[i]->SendMessage(comp_msg);
					connection->contact = 0;
				}
				else if (type == CONTACT_BEGIN) {
					//ComponentMessage comp_msg(CONNECTION, ComponentMessage::CONTACT_BEGIN, (void*)&temp);
					//entities[i]->SendMessage(comp_msg);
					connection->contact = tempID;
				}
			}
		}
	}
}


EntityID ConnectionManager::CheckContact(EntityID idA, EntityID idB, EntityConnection * collision) {
	EntityID searchID = 0;

	if (idA == collision->primaryContact){
		searchID = idB;
	}
	else if (idB == collision->primaryContact){
		searchID = idA;
	}
	else {
		return 0;
	}
	
	for (int i = 0; i < collision->secondaryContacts.size(); i++) {
		if (collision->secondaryContacts[i] == searchID) {
			return searchID;
		}
	}

	return 0;
}


void ConnectionManager::RegisterConnection(EntityID primaryContact, std::vector<EntityID> secondaryContacts, std::string name, bool listenContact) {
	ContactConnection * contact = new ContactConnection;
	contact->connection.primaryContact = primaryContact;
	contact->connection.secondaryContacts = secondaryContacts;
	contact->listenContact = listenContact;
	ConnectionManager::connectionMap.insert(std::pair<std::string, ContactConnection*>(name, contact));
}

void ConnectionManager::RegisterCollisionFilter(EntityID primaryContact, std::vector<EntityID> secondaryContacts){
	EntityConnection * connection = new EntityConnection;
	connection->primaryContact = primaryContact;
	connection->secondaryContacts = secondaryContacts;
	ConnectionManager::collisionFilters.push_back(connection);
}



bool ConnectionManager::GetContactConnection(std::string str, EntityID &primary, EntityID &secondary) {

	auto iter = ConnectionManager::connectionMap.find(str);
	if (iter != ConnectionManager::connectionMap.end()) {
		ContactConnection * connection = iter->second;
		if (connection->listenContact && connection->contact) {
			primary = connection->connection.primaryContact;
			secondary = connection->contact;
			return true;
		}
	}
	return false;
}


void ConnectionManager::GetConnection(std::string str, EntityID &primary, std::vector<EntityID> &secondary) {
	ContactConnection * connection = connectionMap.find(str)->second;
	primary = connection->connection.primaryContact;
	secondary = connection->connection.secondaryContacts;
}


