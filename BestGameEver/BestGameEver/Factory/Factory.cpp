#include "Factory.h"



Factory::Factory()
{
}


Factory::~Factory()
{
}



std::vector<b2Joint*> Factory::CreateJoints(std::vector<Item*> items, RevoluteJointConfig config)
{

	std::vector<b2Joint*> joints;
	for (int i = 1; i < items.size(); i++) {
		b2RevoluteJointDef * jointDef = new b2RevoluteJointDef;
		jointDef->bodyA = items[i - 1]->body;
		jointDef->localAnchorA.Set(config.coordsA[i - 1].x, config.coordsA[i - 1].y);

		jointDef->bodyB = items[i]->body;
		jointDef->localAnchorB.Set(config.coordsB[i - 1].x, config.coordsB[i - 1].y);


		jointDef->collideConnected = config.collide;
		joints.push_back(Globals::world.CreateJoint(jointDef));
	}
	
	return joints;
}


std::vector<b2Joint*> Factory::CreateJoints(Item * itemA, Item * itemB, WheelJointConfig config)
{
	std::vector<b2Joint*> joints;
	b2WheelJointDef * jointDef = new b2WheelJointDef;

	jointDef->localAxisA = config.axis;
	jointDef->bodyA = itemA->body;
	jointDef->localAnchorA.Set(config.coordsA.x, config.coordsA.y);

	jointDef->bodyB = itemB->body;
	jointDef->localAnchorB.Set(config.coordsB.x, config.coordsB.y);

	jointDef->dampingRatio = 5;
	
	jointDef->collideConnected = config.collide;
	joints.push_back(Globals::world.CreateJoint(jointDef));

	return joints;

}



void Factory::CreateItem(Item * item, std::vector<Part*> parts, b2BodyType bodyType) {
	
	item->parts = parts;

	std::vector<b2FixtureDef*> fixtures;

	for (int i = 0; i < parts.size(); i++) {
		if (parts.at(i)->fixtureDef == NULL) { // If any part is missing a fixture, no body assigned
			assert(0); // missing fixture definition for body
		}
		fixtures.push_back(parts.at(i)->fixtureDef);
	}

	item->body = Factory::CreateBody(fixtures, bodyType);
	if (item == NULL) assert(0);
}

Item * Factory::CreateItem(std::vector<Part*> parts, b2BodyType bodyType) {
	Item * item = new Item;
	item->parts = parts;

	std::vector<b2FixtureDef*> fixtures;

	for (int i = 0; i < parts.size(); i++) {
		if (parts.at(i)->fixtureDef == NULL) { // If any part is missing a fixture, no body assigned
			assert(0); // missing fixture definition for body
		}
		fixtures.push_back(parts.at(i)->fixtureDef);
	}

	item->body = Factory::CreateBody(fixtures, bodyType);
	if (item == NULL) assert(0);
	return item;
}


Item * Factory::CreateItem(std::vector<Part*> parts) {
	Item * item = new Item;
	item->parts = parts;
	return item;
}


Part * Factory::_CreatePart(ItemType &userItemType, b2Vec2 center, b2Vec2 size, float angle) {
	// a part needs at least either a sprite or a shape	
	assert(!userItemType.file.empty() || userItemType.shape != NULL);

	// Create Item Fixture
	Part * part = new Part;
	part->center = center;
	part->angle = angle;

	// Create Sprite
	if (!userItemType.file.empty()){
		part->sprite = Factory::CreateSprite(userItemType.file, BOX_2_SF(size.x), BOX_2_SF(size.y), center);
	} //check if sprite was specified
	
	// Create Shape and Fixture
	if (userItemType.shape != NULL) { // No need to assign body if NULL; just a background
		b2Shape * shape = Factory::CreateShape(size, *userItemType.shape, center, angle);
		part->fixtureDef = Factory::CreateFixtureDef(shape, userItemType.material);
	}

	if (part == NULL) assert(0);
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




b2Shape * Factory::CreateShape(b2Vec2 size, ItemShapeType &shapeType, b2Vec2 center, float angle) {
	return shapeType.GetShape(size, center, angle);
}

b2FixtureDef * Factory::CreateFixtureDef(b2Shape * shape, Material  *material) {

	b2FixtureDef * fixtureDef = new b2FixtureDef;
	fixtureDef->shape = shape;
	if (material != NULL) { // come up with better way of doign this
		fixtureDef->density = material->density;
		fixtureDef->friction = material->friction;
		fixtureDef->restitution = material->resitution;
	}
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

