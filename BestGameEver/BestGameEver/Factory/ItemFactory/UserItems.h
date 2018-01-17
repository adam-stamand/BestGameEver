#pragma once
#include "Factory/ItemFactory/ItemType.h"
#include "Factory/Box2DFactory/Box2DFactory.h"
#include "Factory/SFMLFactory/SFMLFactory.h"


class Rocket : public ItemType {
public:
  Rocket() {
    this->file = IMAGE(rocket_ship.png);
    this->material = new Steel;
    this->shape = new PolyFixture({ b2Vec2(.5, 0), b2Vec2(1, 0.65), b2Vec2(1, 1), b2Vec2(0, 1), b2Vec2(0, 0.65) });
  }

};

class Box : public ItemType {
public:
  Box() {
    this->file = IMAGE(box.png);
    this->material = new Wood;
    this->shape = new PolyFixture({ b2Vec2(0, 0), b2Vec2(0,1), b2Vec2(1, 1), b2Vec2(1, 0) });
  }

};


class Balloon : public ItemType {
public:
  Balloon() {
    this->file = IMAGE(balloon.png);
    this->material = new Rubber;
    this->shape = new CircleFixture(.65, b2Vec2(0, -.25));
  }

};

class Character : public ItemType {
public:
  Character() {
    this->file = IMAGE(character.png);
    this->material = new Wood;
    this->shape = new PolyFixture({ b2Vec2(0,0),b2Vec2(0,1),b2Vec2(1,1),b2Vec2(1,0) });

  }

};


class Cannon : public ItemType {
public:
  Cannon() {
    this->file = IMAGE(cannon.png);
    this->material = new Rubber;
    this->shape = new PolyFixture({ b2Vec2(0,0),b2Vec2(0,1),b2Vec2(1,1),b2Vec2(1,0) });

  }

};

class Tire : public ItemType {
public:
  Tire() {
    this->file = IMAGE(tire.png);
    this->material = new Rubber;
    this->shape = new CircleFixture(1, b2Vec2(0, 0));
  }

};

class Tree : public ItemType {
public:
  Tree() {
    this->file = IMAGE(tree.png);
  }

};

class Background : public ItemType {
public:
  Background() {
    this->file = IMAGE(sky_background.png);
  }

};


class Border : public ItemType {
public:
  Border() {
    this->shape = new ChainFixture({ b2Vec2(0, 0), b2Vec2(0,1), b2Vec2(1, 1), b2Vec2(1, 0) });
  }

};


class Platform : public ItemType {
public:
  Platform() {
    this->file = IMAGE(platform.png),
      this->shape = new PolyFixture({ b2Vec2(0, .5), b2Vec2(0,1), b2Vec2(1, 1), b2Vec2(1, .5) });
  }

};

class Car : public ItemType {
public:
  Car() {
    this->file = IMAGE(car.png),
      this->material = new Steel;
    this->shape = new PolyFixture({ b2Vec2(0, 0), b2Vec2(0,1), b2Vec2(1, 1), b2Vec2(1, 0) });
  }

};