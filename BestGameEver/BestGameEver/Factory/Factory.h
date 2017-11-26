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

	static sf::Sprite * CreateSprite(std::string str, int xSize, int ySize);
	static b2Shape * CreateShape(sf::Sprite &sprite, ItemShapeType &shape);
	static b2FixtureDef * CreateFixture(b2Shape *shape, Material &material);
	static b2Body * CreateBody(std::vector<b2FixtureDef*> fixtures, b2BodyType bodyType);

	template <typename T>
	static Item * CreateItem(float xSize, float ySize, uint16_t mask = 0xFFFF, uint16_t category = 0x0001);

private:	
	static Item * _CreateItem(ItemType *userBody, float xSize, float ySize, uint16_t mask, uint16_t category);
};

template <typename T>
Item * Factory::CreateItem(float xSize, float ySize, uint16_t mask, uint16_t category) {
	T * userItem = new T;
	return Factory::_CreateItem(userItem, xSize, ySize, mask, category);
}