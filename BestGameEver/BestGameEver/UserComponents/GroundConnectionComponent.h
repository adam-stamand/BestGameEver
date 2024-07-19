#pragma once

#include "Component/ConnectionComponentBase.h"
#include "Manager/EntityManager.h"

// move to generic component

class GroundConnectionComponent : public ConnectionComponentBase
{
public:


	GroundConnectionComponent(uint32_t objectID, std::vector<uint32_t> groundIDs) : ConnectionComponentBase() {
		this->objectID = objectID;
		this->groundIDs = groundIDs;
	};

	~GroundConnectionComponent() {};


	uint32_t objectID;
	std::vector<uint32_t> groundIDs;
	bool inRange = false;

	void ComponentMessageHandler(ComponentMessage &msg) {

		switch (msg.funcID) {

		case ComponentMessage::JUMP: {
			if (inRange) {
				ComponentMessage comp_msg(PHYSICS, ComponentMessage::APPLY_IMPULSE, msg.params);
				EntityManager::SendMessage(this->objectID, comp_msg);
			}

			break;
		}

		case ComponentMessage::CONTACT_BEGIN: {
			this->inRange = true;
			break;
		}

		case ComponentMessage::GET_IDS: {
			ComponentMessage::Contact * params = (ComponentMessage::Contact*)msg.params;
			params->idVec = this->groundIDs;
			params->idVec.push_back(this->objectID);
			break;
		}



		case ComponentMessage::CONTACT_END: {
			puts("INCsssssssssssONTATONC");
			this->inRange = false;
			break;
		}

		
		}
	}


};