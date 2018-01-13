#pragma once

#include "Component/Message/ComponentMessage.h"


class TestMessage : public ComponentMessage {
public:
	TestMessage() : ComponentMessage(CONNECTION, "TEST") {}
	std::string str;
};