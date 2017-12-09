#pragma once

#include "Component/ConnectionComponentBase.h"
#include "Manager/EntityManager.h"

// move to generic

class VehicleConnectionComponent : public ConnectionComponentBase {
public:


	VehicleConnectionComponent(uint32_t entityAid, uint32_t  entityBid, uint32_t entityCid) : ConnectionComponentBase() {
		this->vehicleID = entityAid;
		this->occupantID = entityBid;
		this->gunID = entityCid;
		EntityManager::DisableComponent(vehicleID, CONTROLS);
		EntityManager::DisableComponent(gunID, CONTROLS);
		EntityManager::DisableComponent(gunID, PHYSICS);
	};

	~VehicleConnectionComponent() {};


	bool occupied = false;
	bool inRange = false;
	uint32_t vehicleID;
	uint32_t occupantID;
	uint32_t gunID;


	void ComponentMessageHandler(ComponentMessage &msg) {

		switch (msg.funcID) {


		case ComponentMessage::GET_IDS: {
			ComponentMessage::Contact * params = (ComponentMessage::Contact*)msg.params;
			params->idVec = {this->vehicleID, this->occupantID};
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

				EntityManager::DisableComponent(vehicleID, CONTROLS);
				EntityManager::DisableComponent(gunID, CONTROLS);
				EntityManager::DisableComponent(gunID, PHYSICS);
				EntityManager::EnableEntity(occupantID);

				ComponentMessage::Transform trans;
				ComponentMessage comp_msg(PHYSICS, ComponentMessage::GET_TRANSFORM, &trans);
				EntityManager::SendMessage(vehicleID, comp_msg);
				
				trans.angle = 0; // we don't want to rotate the character
				comp_msg.funcID = ComponentMessage::SET_TRANSFORM;
				EntityManager::SendMessage(occupantID, comp_msg);

				this->occupied = false;
			}
			else if (this->inRange) {
				
				EntityManager::EnableComponent(vehicleID, CONTROLS);
				EntityManager::EnableComponent(gunID, CONTROLS);
				EntityManager::EnableComponent(gunID, PHYSICS);
				EntityManager::DisableEntity(occupantID);
				this->occupied = true;
			}
			
			break;
		}
		}
	}


};