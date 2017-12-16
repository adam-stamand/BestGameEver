#pragma once

#include <vector>
#include <stdint.h>
#include "Box2D/Box2D.h"

enum CompIDEnum {
	PHYSICS = 0,
	CONTROLS,
	GRAPHICS,
	CONNECTION,
	GENERIC,
	NUM_COMP
};


typedef CompIDEnum ComponentID;
typedef const std::string FuncName;

class ComponentMessage {
public:

	enum MessageDir {
		INPUT,
		OUTPUT
	};

	ComponentMessage(ComponentID compID, FuncName funcName) : 
		funcName(funcName),
		compID(compID)
	{}

	~ComponentMessage() {}
	virtual void SetDirection(MessageDir dir) {
		this->direction = dir;
	}
	MessageDir GetDirection() { return direction; };
	const ComponentID compID;
	const FuncName funcName;

protected:
	MessageDir direction;
};

