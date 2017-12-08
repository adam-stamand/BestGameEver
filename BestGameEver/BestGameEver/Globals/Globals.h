#pragma once
#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"

#define MUSIC(x)			"Music/" #x
#define IMAGE(x)			"Images/" #x
#define WORLD_SCALE			30.0f
#define RAD_2_DEGREES(x)	((x) * 57.295779513)
#define DEGREES_2_RAD(x)	((x) / 57.295779513)
#define SF_2_BOX(x)			((x) / WORLD_SCALE)
#define BOX_2_SF(x)			((x) * WORLD_SCALE)


class Globals {
public:

	static uint32_t GetEntityID();
	static uint32_t GetComponentID();
	static uint32_t GetTimer();
	static void IncrTimer();
	static b2World world;

private:
	static uint32_t globalTimer;
	static uint32_t entityIDCounter;
	static uint32_t componentIDCounter;
};