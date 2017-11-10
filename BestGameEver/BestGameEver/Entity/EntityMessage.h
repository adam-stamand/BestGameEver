#pragma once
#include "ComponentMessage.h"


struct EntityMessage {
	int comp_ID;
	ComponentMessage *comp_msg;
};