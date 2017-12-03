#pragma once
#include "Factory/ItemType.h"
#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"


#define DYNAMIC_BODY	b2BodyType::b2_dynamicBody
#define STATIC_BODY		b2BodyType::b2_staticBody
#define KINEMATIC_BODY	b2BodyType::b2_kinematicBody





class ItemFixture {

public:
	ItemFixture() {};

	sf::Sprite * sprite;
	b2FixtureDef * fixture;
	b2Vec2 center;
	float angle;
};


class Item {

public:
	Item() {};

	std::vector<ItemFixture*> itemFixtures;
	b2Body * body;
};