#include "Factory.h"



Factory::Factory()
{
}


Factory::~Factory()
{
}


Item * Factory::_CreateItem(ItemType *userItemType, float xSize, float ySize, uint16_t mask, uint16_t category) {
	Item * item = new Item;
	std::vector<b2FixtureDef*> fixtures;

	for (int i = 0; i < userItemType->itemFixtures.size(); i++) {

		item->sprites.push_back(Factory::CreateSprite(userItemType->itemFixtures.at(i).file, xSize, ySize));


		b2Shape * shape = Factory::CreateShape(
			*item->sprites.at(i),
			*userItemType->itemFixtures.at(i).shape
		);

		fixtures.push_back(
			Factory::CreateFixture(
				shape,
				*userItemType->itemFixtures.at(i).material
			)
		);
		fixtures.at(i)->filter.categoryBits = category;
		fixtures.at(i)->filter.maskBits = mask;
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




b2Shape * Factory::CreateShape(sf::Sprite &sprite, ItemShapeType &shapeType) {
	
	b2Shape * shape = shapeType.GetShape(sprite);

	return shape;
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

	b2Body * body = Globals::world.CreateBody(bodyDef);
	for (int i = 0; i < fixtures.size(); i++) {
		body->CreateFixture(fixtures.at(i));
	}

	return body;
}

