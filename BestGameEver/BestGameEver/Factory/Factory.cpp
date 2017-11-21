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

		float xSize = item->sprites.at(i)->getTexture()->getSize().x;
		float ySize = item->sprites.at(i)->getTexture()->getSize().y;

		float xScale = item->sprites.at(i)->getScale().x;
		float yScale = item->sprites.at(i)->getScale().y;

		for (int j = 0; j < userItemType->fixtures.at(i).coords.size(); j++) {
			userItemType->fixtures.at(i).coords.at(j).x = (SF_2_BOX(userItemType->fixtures.at(i).coords.at(j).x * xScale * xSize * 1)) - SF_2_BOX((xScale *xSize / 2 * 1));
			userItemType->fixtures.at(i).coords.at(j).y = (SF_2_BOX(userItemType->fixtures.at(i).coords.at(j).y * yScale * ySize * 1)) - SF_2_BOX((yScale *ySize / 2 * 1));
		}

		b2Shape * shape = Factory::CreateShape(
			userItemType->fixtures.at(i).shapeType,
			(b2Vec2*)&userItemType->fixtures.at(i).coords.at(0),
			userItemType->fixtures.at(i).coords.size() 
		);

		fixtures.push_back(
			Factory::CreateFixture(
				shape,
				*userItemType->fixtures.at(i).material
			)
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
		shape->Set(coords, verts);
		return shape;
		break;
	}
	return NULL;
	
}

b2FixtureDef * Factory::CreateFixture(b2Shape * shape, Material &material) {

	b2FixtureDef * fixtureDef = new b2FixtureDef;
	fixtureDef->shape = shape;
	fixtureDef->density = material.density;
	fixtureDef->friction = material.friction;
	fixtureDef->restitution = material.resitution;
	return fixtureDef;
}



b2Body * Factory::CreateBody(std::vector<b2FixtureDef*> fixtures, b2BodyType bodyType) {


	b2BodyDef * bodyDef = new b2BodyDef;
	bodyDef->type = bodyType;

	b2Body * body = world.CreateBody(bodyDef);
	for (int i = 0; i < fixtures.size(); i++) {
		body->CreateFixture(fixtures.at(i));
	}

	return body;
}

