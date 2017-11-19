#pragma once
#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"
#include "Factory/Item.h"
#include "Factory/UserItemType.h"
#include "World/World.h"



class Factory
{
public:
	Factory();
	~Factory();

	static sf::Sprite * CreateSprite(std::string str, int xSize, int ySize);
	static b2Shape * CreateShape(ItemType::ShapeType shape, b2Vec2 coords[], int verts);
	static b2FixtureDef * CreateFixture(ItemType::ShapeType shape, b2Vec2 coords[], int verts, Material &material);
	static b2Body * CreateBody(std::vector<b2FixtureDef*> fixtures, b2BodyType bodyType);

	template <typename T>
	static Item * CreateItem(float xSize, float ySize);

private:	
	static Item * _CreateItem(ItemType *userBody, float xSize, float ySize);
};

template <typename T>
Item * Factory::CreateItem(float xSize, float ySize) {
	T * userItem = new T;
	return Factory::_CreateItem(userItem, xSize, ySize);
}