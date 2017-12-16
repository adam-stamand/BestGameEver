#pragma once

#include <string>

#include "Message/ComponentMessage.h"
#include "Factory/Item.h"
#include "Types.h"


class TransformMessage : public ComponentMessage
{
public:
	TransformMessage() : ComponentMessage(PHYSICS, "TRANSFORM") {}

	flVec2 center;
	float angle;
};

class ItemMessage : public ComponentMessage
{
public:
	ItemMessage() : ComponentMessage(PHYSICS, "ITEM") {}

	Item *item;
};

class VelocityMessage : public ComponentMessage
{
public:
	VelocityMessage() : ComponentMessage(PHYSICS, "VELOCITY") {}

	flVec2 velocity;
};

class ImpulseMessage : public ComponentMessage
{
public:
	ImpulseMessage() : ComponentMessage(PHYSICS, "APPLY_IMPULSE") { this->direction = OUTPUT; }
	void SetDirection(MessageDir dir) { assert(0); };
	flVec2 point;
	flVec2 unitVec;
	float magnitude;
};

class ForceMessage : public ComponentMessage
{
public:
	ForceMessage() : ComponentMessage(PHYSICS, "APPLY_FORCE") { this->direction = OUTPUT; }
	void SetDirection(MessageDir dir) { assert(0); };
	flVec2 unitVec;
	flVec2 point;
	float magnitude;
};

class RayCastMessage : public ComponentMessage
{
public:
	RayCastMessage() : ComponentMessage(PHYSICS, "RAY_CAST") { this->direction = OUTPUT; }
	void SetDirection(MessageDir dir) { assert(0); };
	flVec2 point1;
	flVec2 point2;
	float magnitude;
};