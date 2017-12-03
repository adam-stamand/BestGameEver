#pragma once
#include "Box2D/Box2D.h"
#include <SFML/Graphics.hpp>


class ItemShapeType
{
public:
	ItemShapeType() {};
	~ItemShapeType() {};

	virtual b2Shape * GetShape(sf::Sprite & sprite, b2Vec2 center) = 0;
};

