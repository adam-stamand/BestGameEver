#pragma once
#include "Connector/ConnectionInterface.h"
#include "Components/Components.h"
#include "Entity/EntityInterface.h"

class VehicleConnection : public ControlsComponentBase<VehicleConnection>, public ConnectionInterface
{
public:

	RateLimiter rateLimiter;


	VehicleConnection(Entity *vehicle, Entity *occupant);

	~VehicleConnection();

	void Update() {
		static_cast<ControlsComponentBase<VehicleConnection>*>(this)->Update(*this->vehicle);
	}

	void MessageHandler(ComponentMessage &msg) {
		switch (msg.funcID) {
		}
	};

	bool CheckContact(uint32_t idA, uint32_t idB) {
		return ((idA == this->vehicle->id) && (idB == this->occupant->id)) || ((idA == this->occupant->id) && (idB == this->vehicle->id));
	}

	Entity * vehicle = NULL;
	Entity * occupant = NULL;
	
	void Enter(EntityInterface &entity);


	void HandleBeginContact() {
		this->inRange = true;
	}

	void HandleEndContact() {
		this->inRange = false;
	}


	bool inRange = false;
	bool occupied = false;
};

