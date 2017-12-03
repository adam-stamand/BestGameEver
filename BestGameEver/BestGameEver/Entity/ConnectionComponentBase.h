#pragma once
#include "Entity/ComponentBase.h"
#include "Entity/EntityInterface.h"
#include "Entity/Message.h"
#include "Globals/Globals.h"


class ConnectionComponentBase : public ComponentBase{
public:
	ConnectionComponentBase() : ComponentBase(CONNECTION) {
	};
	~ConnectionComponentBase() {};
		

	virtual void Update(EntityInterface &entity) {};

	EntityInterface * entityA = NULL;
	EntityInterface * entityB = NULL;


};