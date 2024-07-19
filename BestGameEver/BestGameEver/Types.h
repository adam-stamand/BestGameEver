#pragma once
#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"
#include "BloxFW/BloxFW.h"


#define MUSIC(x)			"Music/" #x
#define IMAGE(x)			"Images/" #x
#define WORLD_SCALE			30.0f
#define RAD_2_DEGREES(x)	((x) * 57.295779513)
#define DEGREES_2_RAD(x)	((x) / 57.295779513)
#define PIX_2_BOX(x)			((x) / WORLD_SCALE)
#define BOX_2_PIX(x)			(WORLD_SCALE * (x))


typedef b2Vec2 flVec2;
typedef b2Vec3 flVec3;

typedef bx::BoxID EntityID;
typedef bx::BlockID ComponentID;


