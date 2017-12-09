#include "Manager/ContactManager.h"

// Functions could probably be cleaned up
// Currently no way to Deregister collisionFilter or Contact


void ContactManager::BeginContact(b2Contact* contact) {
	uint32_t idA, idB;
	this->GetIDs(contact, idA, idB);
	if (!idA || !idB) return;

	Entity * connection = SearchContact(contact, idA, idB);
	if (connection != NULL) {
		ComponentMessage comp_msg(CONNECTION, ComponentMessage::CONTACT_BEGIN, NULL);
		connection->SendMessage(comp_msg);
	}
}


void ContactManager::EndContact(b2Contact* contact) {
	uint32_t idA, idB;
	this->GetIDs(contact, idA, idB);
	if (!idA || !idB) return;

	Entity * connection = SearchContact(contact, idA, idB);
	if (connection != NULL) {
		ComponentMessage comp_msg(CONNECTION, ComponentMessage::CONTACT_END, NULL);
		connection->SendMessage(comp_msg);
	}
}


void ContactManager::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
	uint32_t idA, idB;
	this->GetIDs(contact, idA, idB);
	if (!idA || !idB) return;
	
	for (int i = 0; i < collisionFilters.size(); i++) {
		bool temp = this->CheckContact(idA, idB, collisionFilters.at(i));
		if (temp) {
			contact->SetEnabled(false);
		}
	}
}


void ContactManager::GetIDs(b2Contact* contact, uint32_t &idA, uint32_t &idB) {
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


Entity * ContactManager::SearchContact(b2Contact* contact, uint32_t idA, uint32_t idB) {
	ComponentMessage::Contact contactStruct;
	ComponentMessage comp_msg(CONNECTION, ComponentMessage::GET_IDS, &contactStruct);

	for (int i = 0; i < this->entities.size(); i++) {
		entities.at(i)->SendMessage(comp_msg);
		bool temp = this->CheckContact(idA, idB, contactStruct.idVec);

		if (temp) {
			return this->entities.at(i);
		}
	}
	return NULL; // No contact made
}


bool ContactManager::CheckContact(uint32_t idA, uint32_t idB, std::vector<uint32_t> testIDs) {
	bool idA_bool = false;
	bool idB_bool = false;

	for (int i = 0; i < testIDs.size(); i++) {
		if (idA == testIDs.at(i)) {
			idA_bool = true;
		}
		else if (idB == testIDs.at(i)) {
			idB_bool = true;
		}
	}

	return (idA_bool && idB_bool);
}


void ContactManager::RegisterContact(Entity *entity) {
	this->entities.push_back(entity);
}


void ContactManager::RegisterFilter(std::vector<uint32_t> filter) {
	collisionFilters.push_back(filter);
}


