#pragma once
#include "Factory/PartFactory/PartType.h"
#include "Factory/Box2DFactory/Box2DFactory.h"
#include "Factory/SFMLFactory/SFMLFactory.h"


class Rocket_t  : public PartType {
public:
  Rocket_t() {
    this->file = IMAGE(rocket_ship.png);
    this->material = new Steel;
    this->shape = new PolyFixture({ b2Vec2(.5, 0), b2Vec2(1, 0.65), b2Vec2(1, 1), b2Vec2(0, 1), b2Vec2(0, 0.65) });
  }

};

class Cannon_t : public PartType {
public:
  Cannon_t() {
    this->file = IMAGE(cannon.png);
    this->material = new Wood;
    this->shape = new PolyFixture({ b2Vec2(0, 0), b2Vec2(0,1), b2Vec2(1, 1), b2Vec2(1, 0) });
  }

};

class Player_t : public PartType {
public:
  Player_t() {
    this->file = IMAGE(character.png);
    this->material = new Steel;
    this->shape = new PolyFixture({ b2Vec2(0, 0), b2Vec2(0,1), b2Vec2(1, 1), b2Vec2(1, 0) });
  }

};


class Box_t  : public PartType {
public:
  Box_t() {
    this->file = IMAGE(box.png);
    this->material = new Wood;
    this->shape = new PolyFixture({ b2Vec2(0, 0), b2Vec2(0,1), b2Vec2(1, 1), b2Vec2(1, 0) });
  }

};

class Rope_t : public PartType {
public:
  Rope_t() {
    this->file = IMAGE(rope.png);
    this->material = new Feather;
    this->shape = new PolyFixture({ b2Vec2(0, 0), b2Vec2(0,1), b2Vec2(1, 1), b2Vec2(1, 0) });
  }

};


class Balloon_t  : public PartType {
public:
  Balloon_t() {
    this->file = IMAGE(balloon.png);
    this->material = new Rubber;
    this->shape = new CircleFixture(.65, b2Vec2(0, -.25));
  }

};

class Character_t  : public PartType {
public:
  Character_t() {
    this->file = IMAGE(character.png);
    this->material = new Wood;
    this->shape = new PolyFixture({ b2Vec2(0,0),b2Vec2(0,1),b2Vec2(1,1),b2Vec2(1,0) });

  }

};


class Tire_t  : public PartType {
public:
  Tire_t() {
    this->file = IMAGE(tire.png);
    this->material = new Rubber;
    this->shape = new CircleFixture(1, b2Vec2(0, 0));
  }

};

class Tree_t  : public PartType {
public:
  Tree_t() {
    this->file = IMAGE(tree.png);
  }

};

class Background_t  : public PartType {
public:
  Background_t() {
    this->file = IMAGE(sky_background.png);
  }

};


class Border_t  : public PartType {
public:
  Border_t() {
    this->shape = new ChainFixture({ b2Vec2(0, 0), b2Vec2(0,1), b2Vec2(1, 1), b2Vec2(1, 0) });
  }

};


class Platform_t  : public PartType {
public:
  Platform_t() {
    this->file = IMAGE(platform.png),
      this->shape = new PolyFixture({ b2Vec2(0, .5), b2Vec2(0,1), b2Vec2(1, 1), b2Vec2(1, .5) });
  }

};

class Car_t  : public PartType {
public:
  Car_t() {
    this->file = IMAGE(car.png),
      this->material = new Steel;
    this->shape = new PolyFixture({ b2Vec2(0, 0), b2Vec2(0,1), b2Vec2(1, 1), b2Vec2(1, 0) });
  }

};