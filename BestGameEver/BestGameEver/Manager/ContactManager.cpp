#include "Manager/ContactManager.h"

// Functions could probably be cleaned up
// Currently no way to Deregister collisionFilter or Contact

// consider using grouping for contatcts // example; all objects take damage when colliding with ground group


//another idea; you could puts contact handling in the user data of the body, so that
//contact manager just called that, no need to store references to entities; just an idea 
void ContactManager::BeginContact(b2Contact* contact) {
	uint32_t idA, idB;
	this->GetIDs(contact, idA, idB);
	if (!idA || !idB) {
		//puts("ERR: Contact Manager - Invalid ID");
		return;
	}
	SearchContact(idA, idB, CONTACT_BEGIN);
}


void ContactManager::EndContact(b2Contact* contact) {
	uint32_t idA, idB;
	this->GetIDs(contact, idA, idB);
	if (!idA || !idB) {
		//puts("ERR: Contact Manager - Invalid ID");
		return;
	}
	SearchContact(idA, idB, CONTACT_END);
}


void ContactManager::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
	uint32_t idA, idB;
	this->GetIDs(contact, idA, idB);
	if (!idA || !idB) {
		//puts("ERR: Contact Manager - Invalid ID");
		return;
	}

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


void ContactManager::SearchContact(uint32_t idA, uint32_t idB, ContactType type) {

	for (int i = 0; i < this->entities.size(); i++) {
		if (entities[i]->GetID() == idA || entities[i]->GetID() == idB) {
			uint32_t temp = idA;
			if (entities[i]->GetID() == idA) {
				temp = idB;
			}
			if (type == CONTACT_END) {
				ComponentMessage comp_msg(CONNECTION, ComponentMessage::CONTACT_END, (void*)&temp);

				entities[i]->SendMessage(comp_msg);
			}
			else if (type == CONTACT_BEGIN) {
				ComponentMessage comp_msg(CONNECTION, ComponentMessage::CONTACT_BEGIN, (void*)&temp);

				entities[i]->SendMessage(comp_msg);
			}
		}
	}
}


bool ContactManager::CheckContact(uint32_t idA, uint32_t idB, std::vector<uint32_t> idVec) {
	bool idA_bool = false;
	bool idB_bool = false;
	
	if (idVec[0] == idA){
		for (int i = 1; i < idVec.size(); i++) {
			if (idB == idVec[i]) {
				return true;
			}
		}
	}
	else if (idVec[0] == idB) {
		for (int i = 1; i < idVec.size(); i++) {
			if (idA == idVec[i]) {
				return true;
			}
		}
	}

	return false;
}


void ContactManager::RegisterContact(Entity *entity) {
	this->entities.push_back(entity);
}


void ContactManager::RegisterFilter(std::vector<uint32_t> filter) {
	collisionFilters.push_back(filter);
}


