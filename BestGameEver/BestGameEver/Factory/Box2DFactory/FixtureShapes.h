#pragma once

#include <assert.h>
#include <vector>
#include "Box2D/Box2D.h"

class FixtureShape
{
public:
  FixtureShape() {};
  ~FixtureShape() {};

  virtual b2Shape * GetShape(b2Vec2 size, b2Vec2 center, float angle) = 0;
};




class CircleFixture : public FixtureShape {

public:
  CircleFixture(float rad, b2Vec2 pnt) { radius = rad; point = pnt; };
  ~CircleFixture() {};

  float radius;
  b2Vec2 point;
  b2Shape * GetShape(b2Vec2 size, b2Vec2 center, float angle);

};

class PolyFixture : public FixtureShape {

public:
  PolyFixture(std::vector<b2Vec2> inputCoords) {
    assert(inputCoords.size() <= 8); // Limitation of box2d // check what happens in box2d if 9 is passed  
    coords = inputCoords;
  };

  ~PolyFixture() {};

  std::vector<b2Vec2> coords;

  b2Shape * GetShape(b2Vec2 size, b2Vec2 center, float angle);

};

class ChainFixture : public FixtureShape {

public:
  ChainFixture(std::vector<b2Vec2> inputCoords) { coords = inputCoords; };
  ~ChainFixture() {};

  std::vector<b2Vec2> coords;

  b2Shape * GetShape(b2Vec2 size, b2Vec2 center, float angle);

};
