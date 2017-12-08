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

	
	template <typename T>
	static Part * CreatePart(b2Vec2 center, b2Vec2 size, float angle = 0, uint16_t mask = 0xFFFF, uint16_t category = 0x0001);

	static Item * CreateItem(std::vector<Part*> parts, b2BodyType bodyType);

private:	
	static sf::Sprite * CreateSprite(std::string str, int xSize, int ySize, b2Vec2 center);
	static b2Shape * CreateShape(sf::Sprite &sprite, ItemShapeType &shape, b2Vec2 center, float angle);
	static b2FixtureDef * CreateFixtureDef(b2Shape *shape, Material &material);
	static b2Body * CreateBody(std::vector<b2FixtureDef*> fixtures, b2BodyType bodyType);

	
	static Part * _CreatePart(ItemType &userBody, b2Vec2 center,  b2Vec2 size, float angle,  uint16_t mask, uint16_t category);
};

template <typename T>
Part * Factory::CreatePart(b2Vec2 center, b2Vec2 size, float angle, uint16_t mask, uint16_t category) {
	T userItem;
	return Factory::_CreatePart(userItem, center, size, angle, mask, category);
}