#include "Factory.h"



Factory::Factory()
{
}


Factory::~Factory()
{
}


Item * Factory::_CreateItem(ItemType *userItemType, float xSize, float ySize) {
	Item * item = new Item;
	std::vector<b2FixtureDef*> fixtures;

	for (int i = 0; i < userItemType->fixtures.size(); i++) {

		item->sprites.push_back(Factory::CreateSprite(userItemType->fixtures.at(i).file, xSize, ySize));

		// TODO:Resize coords here
		float xSize = item->sprites.at(i)->getTexture()->getSize().x;
		float ySize = item->sprites.at(i)->getTexture()->getSize().y;

		float xScale = item->sprites.at(i)->getScale().x;
		float yScale = item->sprites.at(i)->getScale().y;

		for (int j = 0; j < userItemType->fixtures.at(i).coords.size(); j++) {
			userItemType->fixtures.at(i).coords.at(j).x = (userItemType->fixtures.at(i).coords.at(j).x * xScale * xSize * 1 / 30) - (xScale *xSize / 2 * 1 / 30);
			userItemType->fixtures.at(i).coords.at(j).y = (userItemType->fixtures.at(i).coords.at(j).y * yScale * ySize * 1 / 30) - (yScale *ySize / 2 * 1 / 30);
		}

		fixtures.push_back(Factory::CreateFixture(
			userItemType->fixtures.at(i).shapeType,
			(b2Vec2*)&userItemType->fixtures.at(i).coords.at(0),
			userItemType->fixtures.at(i).coords.size(),
			*userItemType->fixtures.at(i).material)
		);
	}
	item->body = Factory::CreateBody(fixtures, userItemType->bodyType);
	item->body->GetFixtureList();
	return item;
}



sf::Sprite * Factory::CreateSprite(std::string str, int xSize, int ySize) {

	sf::Texture * texture = new sf::Texture;
	texture->loadFromFile(str);
	sf::Sprite * sprite = new sf::Sprite;

	sprite->setTexture(*texture);
	float currX, currY, scaleX, scaleY;
	currX = (float)texture->getSize().x;
	currY = (float)texture->getSize().y;

	scaleX = xSize / currX;
	scaleY = ySize / currY;

	sprite->setScale(scaleX, scaleY);
	sprite->setOrigin(currX / 2, currY / 2);
	return sprite;
}




b2Shape * Factory::CreateShape(ItemType::ShapeType shape, b2Vec2 coords[], int verts) {
	
	switch (shape) {
	case ItemType::POLYGON:
		b2PolygonShape * shape = new b2PolygonShape;
		puts("SDFDS");
		shape->Set(coords, verts);
		return shape;
		break;
	}
	
}

b2FixtureDef * Factory::CreateFixture(ItemType::ShapeType shape, b2Vec2 coords[], int verts, Material &material) {

	b2FixtureDef * fixtureDef = new b2FixtureDef;
	fixtureDef->shape = Factory::CreateShape(shape, coords, verts);
	fixtureDef->density = material.density;
	fixtureDef->friction = material.friction;
	fixtureDef->restitution = material.resitution;
	return fixtureDef;
}



b2Body * Factory::CreateBody(std::vector<b2FixtureDef*> fixtures, b2BodyType bodyType) {


	b2BodyDef * bodyDef = new b2BodyDef;
	bodyDef->type = bodyType;
	bodyDef->position.Set(200/30, 200/30);

	b2Body * body = world.CreateBody(bodyDef);
	for (int i = 0; i < fixtures.size(); i++) {
		body->CreateFixture(fixtures.at(i));
	}

	return body;
}

