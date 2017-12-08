#include "Factory.h"



Factory::Factory()
{
}


Factory::~Factory()
{
}


Item * Factory::CreateItem(std::vector<Part*> parts, b2BodyType bodyType) {
	Item * item = new Item;
	item->parts = parts;

	std::vector<b2FixtureDef*> fixtures;

	for (int i = 0; i < parts.size(); i++) {
		if (parts.at(i)->fixtureDef == NULL) { // If any part is missing a fixture, no body assigned
			return item;
		}
		fixtures.push_back(parts.at(i)->fixtureDef);
	}

	item->body = Factory::CreateBody(fixtures, bodyType);

	return item;
}



Part * Factory::_CreatePart(ItemType &userItemType, b2Vec2 center, b2Vec2 size, float angle, uint16_t mask, uint16_t category) {
	
	// Create Item Fixture
	Part * part = new Part;
	part->center = center;
	part->angle = angle;

	// Create Sprite
	part->sprite = Factory::CreateSprite(userItemType.file, BOX_2_SF(size.x), BOX_2_SF(size.y), center);

	if (userItemType.material == NULL || userItemType.shape == NULL) { // No need to assign body; just a background
		part->fixtureDef = NULL;
		return part;
	}

	// Create Shape
	b2Shape * shape = Factory::CreateShape(*part->sprite, *userItemType.shape, center, angle);

	// Create Fixutre
	part->fixtureDef = Factory::CreateFixtureDef(shape, *userItemType.material);
	
	// Apply collision masks
	//itemFixture->fixture->filter.categoryBits = category;
	//itemFixture->fixture->filter.maskBits = mask;

	return part;
}



sf::Sprite * Factory::CreateSprite(std::string str, int xSize, int ySize, b2Vec2 center) {

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
	// setOrigin is done in original Sprite coordinates! (before scaling)
	sprite->setOrigin(currX / 2, currY / 2);
	return sprite;
}




b2Shape * Factory::CreateShape(sf::Sprite &sprite, ItemShapeType &shapeType, b2Vec2 center, float angle) {
	return shapeType.GetShape(sprite, center, angle);
}

b2FixtureDef * Factory::CreateFixtureDef(b2Shape * shape, Material &material) {

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

