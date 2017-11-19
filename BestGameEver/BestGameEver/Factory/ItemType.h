#pragma once

#include "Box2D/Box2D.h"
#include <SFML/Graphics.hpp>
#include "Factory/Material.h"

#define IMAGE(x)		"Images/" #x
#define DYNAMIC_BODY	b2BodyType::b2_dynamicBody
#define STATIC_BODY		b2BodyType::b2_staticBody
#define KINEMATIC_BODY	b2BodyType::b2_kinematicBody




class ItemType
{
public:


	enum ShapeType {
		POLYGON,
		CIRCLE,
		CHAIN,
		LOOP
	};



	struct ItemFixture {
		std::string file;
		ShapeType shapeType;
		Material * material;
		std::vector<b2Vec2> coords;

		ItemFixture(
			std::string str,
			ShapeType shape,
			Material * mat,
			std::vector<b2Vec2> vec) :
			file(str),
			shapeType(shape),
			material(mat),
			coords(vec)
		{}
	};



	ItemType(){};
	~ItemType() {};

	std::vector<ItemFixture> fixtures;
	b2BodyType bodyType;
	
};

