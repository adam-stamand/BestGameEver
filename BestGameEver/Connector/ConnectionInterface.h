#pragma once
#include <stdint.h>

class ConnectionInterface
{
public:
	ConnectionInterface() {};
	~ConnectionInterface() {};

	virtual void Update() = 0;
	virtual void HandleBeginContact()  = 0;
	virtual void HandleEndContact() = 0;
	virtual bool CheckContact(uint32_t idA, uint32_t idB) = 0;
};

