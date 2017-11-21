#pragma once
#include <SFML/Graphics.hpp>

#include "Box2D/Box2D.h"

#define WORLD_SCALE 30
#define RAD_2_DEGREES(x)	(x * 57.295779513)
#define DEGREES_2_RAD(x)	(x / 57.295779513)
#define SF_2_BOX(x)			(x / WORLD_SCALE)
#define BOX_2_SF(x)			(x * WORLD_SCALE)


extern b2World world;
