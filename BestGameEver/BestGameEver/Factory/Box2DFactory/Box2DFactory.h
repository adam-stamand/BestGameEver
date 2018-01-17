#pragma once
#include "Box2D/Box2D.h"
#include "Factory/Box2DFactory/UserMaterials.h"
#include <vector>

#define DYNAMIC_BODY	b2BodyType::b2_dynamicBody
#define STATIC_BODY		b2BodyType::b2_staticBody
#define KINEMATIC_BODY	b2BodyType::b2_kinematicBody



struct RevoluteJointConfig {
  bool collide;
  std::vector<b2Vec2> coordsA;
  std::vector<b2Vec2> coordsB;
};

struct PulleyJointConfig {



};

struct RopeJointConfig {



};

struct WheelJointConfig {
  bool collide;
  b2Vec2 axis;
  b2Vec2 coordsA;
  b2Vec2 coordsB;

};



class Box2DFactory
{
public:
  Box2DFactory();
  ~Box2DFactory();



  // static std::vector<b2Joint*> CreateJoints(std::vector<Item*> items, RevoluteJointConfig config);
  //static std::vector<b2Joint*> CreateJoints(Item* itemA, Item* itemB, WheelJointConfig config);

  template <typename MATERIAL>
  static b2FixtureDef * CreateFixture(b2Shape *shape, b2Vec2 size, b2Vec2 center, float angle = 0);
  static b2FixtureDef * CreateFixture(b2Shape *shape, Material *material, b2Vec2 size, b2Vec2 center, float angle = 0);


  static b2Body * CreateBody(std::vector<b2FixtureDef*> fixtures, b2BodyType bodyType = DYNAMIC_BODY, std::string worldName = "init");
  static b2FixtureDef * _CreateFixture(b2Shape * shape, Material *material, b2Vec2 size, b2Vec2 center, float angle);


};

template <typename MATERIAL>
b2FixtureDef * Box2DFactory::CreateFixture(b2Shape* shape, b2Vec2 size, b2Vec2 center, float angle) {
  MATERIAL * material = new MATERIAL;
  return Box2DFactory::_CreateFixture(shape, material, center, size, angle);
}
