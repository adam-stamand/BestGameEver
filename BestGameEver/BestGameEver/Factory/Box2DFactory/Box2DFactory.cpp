#include "Box2DFactory.h"
#include "Manager/Box2DManager/Box2DManager.h"
#include "BaseComponents/Message.h"

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

  if (fixtures.size() == 0) {
    return NULL;
  }
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




b2Joint* Box2DFactory::CreateJoint(b2Body * bodyA, b2Body * bodyB, RevoluteJointConfig config)
{
  assert(bodyA!=NULL && bodyB!=NULL);
  b2Joint* joint;

  b2RevoluteJointDef * jointDef = new b2RevoluteJointDef;
  jointDef->bodyA = bodyA;
  jointDef->localAnchorA.Set(config.pointA.x, config.pointA.y);

  jointDef->bodyB = bodyB;
  jointDef->localAnchorB.Set(config.pointB.x, config.pointB.y);


  jointDef->collideConnected = config.collide;
  b2World * world;
  Box2DManager::GetWorld(config.worldName, world); //TODO Check RV
  joint = world->CreateJoint(jointDef);
  
  return joint;
}

/*
b2Joint* Box2DFactory::CreateJoint(WheelJointConfig config)
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

*/

