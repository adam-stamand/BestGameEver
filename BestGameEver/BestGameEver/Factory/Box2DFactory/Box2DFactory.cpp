#include "Box2DFactory.h"
#include "Manager/Box2DManager/Box2DManager.h"


Box2DFactory::Box2DFactory()
{
}


Box2DFactory::~Box2DFactory()
{
}


b2FixtureDef * Box2DFactory::CreateFixture(b2Shape * shape, Material * material, b2Vec2 size, b2Vec2 center, float angle) {

  // Create Item Fixture
  b2FixtureDef * fixture = new b2FixtureDef;

  // Create Shape and Fixture
  fixture->shape = shape;
  if (material != NULL) {
    fixture->density = material->density;
    fixture->friction = material->friction;
    fixture->restitution = material->resitution;
  }
  return fixture;
}

b2FixtureDef * Box2DFactory::_CreateFixture(b2Shape * shape, Material * material, b2Vec2 size, b2Vec2 center, float angle) {

  // Create Item Fixture
  b2FixtureDef * fixture = new b2FixtureDef;

  // Create Shape and Fixture
  fixture->shape = shape;
  fixture->density = material->density;
  fixture->friction = material->friction;
  fixture->restitution = material->resitution;
  return fixture;
}


b2Body * Box2DFactory::CreateBody(std::vector<b2FixtureDef*> fixtures, b2BodyType bodyType, std::string name) {


  b2BodyDef * bodyDef = new b2BodyDef;
  bodyDef->type = bodyType;

  b2Body * body;
  b2World * world;
  int rv = Box2DManager::GetWorld(name, world);
  body = world->CreateBody(bodyDef);

  for (int i = 0; i < fixtures.size(); i++) {
    b2FixtureDef * fixture = fixtures.at(i);
    if (fixture != NULL) {
      body->CreateFixture(fixtures.at(i));
    }
  }
  return body;
}