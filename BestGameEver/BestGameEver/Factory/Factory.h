#pragma once
#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"
#include "Factory/Item.h"
#include "Factory/UserItemType.h"
#include "Globals/Globals.h"
#include "Factory/ItemShapeType.h"


struct RevoluteJointConfig {
	bool collide;
	std::vector<b2Vec2> coordsA;
	std::vector<b2Vec2> coordsB;
};

struct PulleyJointConfig {



};

struct RopeJointConfig {



};

struct WheelJointConfig {



};


class Factory
{
public:
	Factory();
	~Factory();

	
	static std::vector<b2Joint*> CreateJoints(std::vector<Item*> items, RevoluteJointConfig config);

	template <typename T>
	static Part * CreatePart(b2Vec2 center, b2Vec2 size, float angle = 0);

	static Item * CreateItem(std::vector<Part*> parts, b2BodyType bodyType);
	static Item * Factory::CreateItem(std::vector<Part*> parts);

private:	
	static sf::Sprite * CreateSprite(std::string str, int xSize, int ySize, b2Vec2 center);
	static b2Shape * CreateShape(b2Vec2 size, ItemShapeType &shape, b2Vec2 center, float angle);
	static b2FixtureDef * CreateFixtureDef(b2Shape *shape, Material *material);
	static b2Body * CreateBody(std::vector<b2FixtureDef*> fixtures, b2BodyType bodyType);

	
	static Part * _CreatePart(ItemType &userBody, b2Vec2 center,  b2Vec2 size, float angle);
};

template <typename T>
Part * Factory::CreatePart(b2Vec2 center, b2Vec2 size, float angle) {
	T userItem;
	return Factory::_CreatePart(userItem, center, size, angle);
}