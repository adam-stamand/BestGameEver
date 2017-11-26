#pragma once

#include "Box2D/Box2D.h"
#include <SFML/Graphics.hpp>
#include "Factory/Material.h"
#include "Factory/ItemShapeType.h"


#define DYNAMIC_BODY	b2BodyType::b2_dynamicBody
#define STATIC_BODY		b2BodyType::b2_staticBody
#define KINEMATIC_BODY	b2BodyType::b2_kinematicBody




class ItemType
{
public:



	struct ItemFixture {
		std::string file;
		Material * material;
		ItemShapeType * shape;

		ItemFixture(
			std::string str,
			Material * mat,
			ItemShapeType * shp) :
			file(str),
			material(mat),
			shape(shp)
		{};
	};



	ItemType(){};
	~ItemType() {};

	std::vector<ItemFixture> itemFixtures;
	b2BodyType bodyType;
	
};

