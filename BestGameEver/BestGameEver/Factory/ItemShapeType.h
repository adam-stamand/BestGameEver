#pragma once
#include "Box2D/Box2D.h"
#include <SFML/Graphics.hpp>


class ItemShapeType
{
public:
	ItemShapeType() {};
	~ItemShapeType() {};

	virtual b2Shape * GetShape(b2Vec2 size, b2Vec2 center, float angle) = 0;
};

