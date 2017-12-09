#pragma once

#include "Box2D/Box2D.h"
#include <SFML/Graphics.hpp>
#include "Factory/Material.h"
#include "Factory/ItemShapeType.h"

#define DYNAMIC_BODY	b2BodyType::b2_dynamicBody
#define STATIC_BODY		b2BodyType::b2_staticBody
#define KINEMATIC_BODY	b2BodyType::b2_kinematicBody

enum BodyType {
	dynamicBody = b2BodyType::b2_dynamicBody,
	staticBody = b2BodyType::b2_staticBody,
	kinematicBody = b2BodyType::b2_kinematicBody,
	voidBody
};



class ItemType
{
public:


	ItemType() {};
	~ItemType() {};

	std::string file;
	Material * material = NULL;
	ItemShapeType * shape = NULL;
};

