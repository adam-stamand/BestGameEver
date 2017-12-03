#pragma once
#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"
#include "Factory/Item.h"
#include "Factory/UserItemType.h"
#include "Globals/Globals.h"
#include "Factory/ItemShapeType.h"




class Factory
{
public:
	Factory();
	~Factory();

	static sf::Sprite * CreateSprite(std::string str, int xSize, int ySize, b2Vec2 center);
	static b2Shape * CreateShape(sf::Sprite &sprite, ItemShapeType &shape, b2Vec2 center);
	static b2FixtureDef * CreateFixture(b2Shape *shape, Material &material);
	static b2Body * CreateBody(std::vector<b2FixtureDef*> fixtures, b2BodyType bodyType);

	template <typename T>
	static ItemFixture * CreateItemFixture(b2Vec2 center, b2Vec2 size, float angle = 0, uint16_t mask = 0xFFFF, uint16_t category = 0x0001);

	static Item * CreateItem(std::vector<ItemFixture*> fixtures, b2BodyType bodyType);

private:	
	static ItemFixture * _CreateItemFixture(ItemType &userBody, b2Vec2 center,  b2Vec2 size, float angle,  uint16_t mask, uint16_t category);
};

template <typename T>
ItemFixture * Factory::CreateItemFixture(b2Vec2 center, b2Vec2 size, float angle, uint16_t mask, uint16_t category) {
	T userItem;
	return Factory::_CreateItemFixture(userItem, center, size, angle, mask, category);
}