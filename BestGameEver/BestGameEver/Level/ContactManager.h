#pragma once
#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"
#include "Entity/Entity.h"


class ContactManager : public b2ContactListener
{
public:
	ContactManager() {};
	~ContactManager() {};


	void BeginContact(b2Contact* contact) {
		uint32_t idA, idB;
		this->GetIDs(contact, idA, idB);
		EntityInterface * connection = SearchContact(contact, idA, idB);
		if (connection != NULL) {
			ComponentMessage comp_msg(CONNECTION, ComponentMessage::CONTACT_BEGIN, NULL);
			connection->SendMessage(comp_msg);
		}
	}


	void EndContact(b2Contact* contact) {
		uint32_t idA, idB;
		this->GetIDs(contact, idA, idB);
		EntityInterface * connection = SearchContact(contact, idA, idB);
		if (connection != NULL) {
			ComponentMessage comp_msg(CONNECTION, ComponentMessage::CONTACT_END, NULL);
			connection->SendMessage(comp_msg);
		}
	}

	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
		uint32_t idA, idB;
		this->GetIDs(contact, idA, idB);

		for (int i = 0; i < collisionFilters.size(); i++) {
			bool temp = this->CheckContact(idA, idB, collisionFilters.at(i));
			if (temp) {
				contact->SetEnabled(false);
			}
		}	
	}

	void GetIDs(b2Contact* contact, uint32_t &idA, uint32_t &idB) {
		void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
		void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

		if (!(bodyUserDataA && bodyUserDataB)) {
			idA = 0;
			idB = 0;
			return;
		}

		Entity * entityA = static_cast<Entity*>(bodyUserDataA);
		Entity * entityB = static_cast<Entity*>(bodyUserDataB);

		idA = entityA->id;
		idB = entityB->id;
	}

	EntityInterface * SearchContact(b2Contact* contact, uint32_t idA, uint32_t idB) {
		ComponentMessage::Contact contactStruct;
		ComponentMessage comp_msg(CONNECTION, ComponentMessage::GET_IDS, &contactStruct);

		for (int i = 0; i < this->entities.size(); i++) {
			entities.at(i)->SendMessage(comp_msg);
			std::vector<uint32_t> idVec{ contactStruct.idA, contactStruct.idB };
			bool temp = this->CheckContact(idA, idB, idVec);

			if (temp) {
				return this->entities.at(i);
			}
		}
		return NULL;
	}

	bool CheckContact(uint32_t idA, uint32_t idB, std::vector<uint32_t> testIDs) {
		bool idA_bool = false, idB_bool = false;
		
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

	void RegisterContact(EntityInterface *entity) {
		this->entities.push_back(entity);
	}

	void RegisterFilter(std::vector<uint32_t> filter) {
		collisionFilters.push_back(filter);
	}

private:
	std::vector<EntityInterface*> entities;
	std::vector<std::vector<uint32_t>> collisionFilters;
	


};

