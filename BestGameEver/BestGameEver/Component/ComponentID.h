#pragma once
#include <map>

enum ComponentID {
	PHYSICS = 0,
	CONTROLS,
	GRAPHICS,
	CONNECTION,
	GENERIC,
	NUM_COMP
};

extern std::map<ComponentID, const char*> componentIDMap;