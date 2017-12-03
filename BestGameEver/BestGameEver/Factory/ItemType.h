#pragma once

#include "Box2D/Box2D.h"
#include <SFML/Graphics.hpp>
#include "Factory/Material.h"
#include "Factory/ItemShapeType.h"





class ItemType
{
public:


	ItemType(){};
	~ItemType() {};

	std::string file;
	Material * material;
	ItemShapeType * shape;
	b2BodyType bodyType;
	
};

