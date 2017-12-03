#include "Connector/VehicleConnection.h"



VehicleConnection::VehicleConnection(Entity *vehicle, Entity *occupant) : ControlsComponentBase(this), rateLimiter(20) {

	vehicle->DisableComponent(CONTROLS);
	this->occupant = occupant;
	this->vehicle = vehicle;
	this->occupied = false;
	this->inRange = false;

	this->RegisterAction(
		{ sf::Keyboard::E },
		{ &ControlsComponent_t::Enter }
	);

}

VehicleConnection::~VehicleConnection()
{
}






void VehicleConnection::Enter(EntityInterface &entity) {
	if (rateLimiter.Check()) {
		if (this->occupied) {
			vehicle->DisableComponent(CONTROLS);
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
			EntityManager::DisableEntity(this->occupant->id);
			this->occupied = true;
		}
	}
	

}