#pragma once

#include "Component/ComponentBase.h"


// Turn this into generic component

class ConnectionComponentBase : public ComponentBase
{
public:
	ConnectionComponentBase() : ComponentBase(CONNECTION) {};
	~ConnectionComponentBase() {};
		
	void Update() { ComponentUpdate(); };	
	void MessageHandler(ComponentMessage &msg) {ComponentMessageHandler(msg);};
	
	virtual void ComponentMessageHandler(ComponentMessage &msg) {};
	virtual void ComponentUpdate() {};
};