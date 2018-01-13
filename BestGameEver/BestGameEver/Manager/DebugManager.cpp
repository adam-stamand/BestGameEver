#include "Manager/DebugManager.h"

const std::map<ComponentID, const char*> DebugManager::componentIDMap = {
	{ PHYSICS, "PHYSICS" },
	{ CONTROLS, "CONTROLS" },
	{ GRAPHICS, "GRAPHICS" },
	{ CONNECTION, "CONNECTION" },
	{ GENERIC, "GENERIC" },
};


