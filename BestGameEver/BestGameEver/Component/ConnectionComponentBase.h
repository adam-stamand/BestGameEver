#pragma once

#include "Component/ComponentBase.h"
#include "Component/Message/Message.h"
//--TODO--//
//Move into separate thing completely

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

		ComponentMessageHandler(msg);
	}
	

	virtual void ComponentUpdate() {};




	std::vector<uint32_t> entityIDs;
};