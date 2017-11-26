#pragma once
#include "Factory/ItemShapeType.h"


class CircleItem : public ItemShapeType {

public:
	CircleItem(float rad, b2Vec2 pnt) { radius = rad; point = pnt; };
	~CircleItem() {};

	float radius;
	b2Vec2 point;
	b2Shape * GetShape(sf::Sprite &sprite);

};

class PolyItem : public ItemShapeType {

public:
	PolyItem(std::vector<b2Vec2> inputCoords) { coords = inputCoords; };
	~PolyItem() {};
	
	std::vector<b2Vec2> coords;

	b2Shape * GetShape(sf::Sprite &sprite);

};