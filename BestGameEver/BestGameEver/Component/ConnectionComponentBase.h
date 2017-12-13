#pragma once

#include "Component/ComponentBase.h"


// Turn this into generic component

class ConnectionComponentBase : public ComponentBase
{
public:
	ConnectionComponentBase(std::vector<uint32_t> entityIDs) : ComponentBase(CONNECTION) {
		this->entityIDs = entityIDs;
	};

	~ConnectionComponentBase() {};
		

	virtual void BeginContact(uint32_t id) {};
	virtual void EndContact(uint32_t id) {};

	void Update() { ComponentUpdate(); }	

	void MessageHandler(ComponentMessage &msg) {
		

		switch (msg.funcID) {

		case ComponentMessage::CONTACT_BEGIN: {
			uint32_t * id = (uint32_t*)msg.params;
			BeginContact(*id);
			break;
		}

		case ComponentMessage::CONTACT_END: {
			uint32_t * id = (uint32_t*)msg.params;
			EndContact(*id);
			break;
		}

		case ComponentMessage::GET_IDS: {
			ComponentMessage::Contact * params = (ComponentMessage::Contact*)msg.params;
			//params->idVec = this->entityIDs;
			//params->idVec.push_back(this->GetEntityID());
			break;
		}


		}

		ComponentMessageHandler(msg);
	}
	


	virtual void ComponentMessageHandler(ComponentMessage &msg) {};
	virtual void ComponentUpdate() {};




	std::vector<uint32_t> entityIDs;
};