#pragma once

#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"
#include "Entity/Entity.h"
#include "Connector/ConnectionBase.h"
#include "Entity/ComponentBase.h"

class Connector
{
public:
	Connector(std::vector<ConnectionInterface*> connections) { this->connections = connections; };
	~Connector() {};

	std::vector<ConnectionInterface*> connections;

	void Update() {
		connection->Update();
	}

	bool CheckContact(uint32_t idA, uint32_t idB) {
		return connection->CheckContact(idA, idB);
	}

	void HandleBeginContact() {
		connection->HandleBeginContact();
	}

	void HandleEndContact() {
		connection->HandleEndContact();
	}

private:


};

