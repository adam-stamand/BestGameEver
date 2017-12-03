#pragma once

#include "Entity/ConnectionComponentBase.h"
#include "Level/EntityManager.h"


class VehicleConnectionComponent : public ConnectionComponentBase {
public:


	VehicleConnectionComponent(EntityInterface *entityA, EntityInterface* entityB, EntityInterface* entityC) : ConnectionComponentBase() {
		this->vehicle = entityA;
		this->occupant = entityB;
		this->gun = entityC;
		vehicle->DisableComponent(CONTROLS);
		gun->DisableComponent(CONTROLS);
		gun->DisableComponent(PHYSICS);
	};

	~VehicleConnectionComponent() {};


	bool occupied = false;
	bool inRange = false;
	EntityInterface * vehicle;
	EntityInterface * occupant;
	EntityInterface * gun;


	void MessageHandler(ComponentMessage &msg) {

		switch (msg.funcID) {


		case ComponentMessage::GET_IDS: {
			ComponentMessage::Contact * params = (ComponentMessage::Contact*)msg.params;
			params->idA = this->vehicle->id;
			params->idB = this->occupant->id;
			break;
		}

		case ComponentMessage::CONTACT_BEGIN: {
			this->inRange = true;
			break;
		}

		case ComponentMessage::CONTACT_END: {
			this->inRange = false;
			break;
		}
		case ComponentMessage::ENTER: {
			if (this->occupied) {
				vehicle->DisableComponent(CONTROLS);
				gun->DisableComponent(CONTROLS);
				gun->DisableComponent(PHYSICS);
				EntityManager::EnableEntity(this->occupant->id);

				ComponentMessage::Transform trans;

				ComponentMessage comp_msg(PHYSICS, ComponentMessage::GET_TRANS, &trans);
				this->vehicle->SendMessage(comp_msg);

				comp_msg.funcID = ComponentMessage::SET_TRANS;
				this->occupant->SendMessage(comp_msg);

				this->occupied = false;
			}
			else if (this->inRange) {
				
				vehicle->EnableComponent(CONTROLS);
				gun->EnableComponent(CONTROLS);
				gun->EnableComponent(PHYSICS);
				EntityManager::DisableEntity(this->occupant->id);
				this->occupied = true;
			}
			
			break;
		}
		}
	}


};