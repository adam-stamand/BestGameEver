#pragma once

#include "Box2D/Box2D.h"
#include <SFML/Graphics.hpp>
#include "Factory/Box2DFactory/Box2DFactory.h"
#include "Factory/SFMLFactory/SFMLFactory.h"
#include "Factory/Box2DFactory/FixtureShapes.h"



class ItemType
{
public:


	ItemType() {};
	~ItemType() {};

	std::string file;
	Material * material = NULL;
	FixtureShape * shape = NULL;
};
