#pragma once
#include "Factory/Box2DFactory/Material.h"


class Steel : public Material {

public:
  Steel() {
    this->density = 5.0f;
    this->friction = 25.0f;
    this->resitution = .1f;
  };

};

class Wood : public Material {

public:
  Wood() {
    this->density = 2.0f;
    this->friction = 30.0f;
    this->resitution = .25f;
  };

};

class Rubber : public Material {

public:
  Rubber() {
    this->density = 1.0f;
    this->friction = 75.0f;
    this->resitution = .5f;
  };

};


class Feather : public Material {

public:
  Feather() {
    this->density = 1.5f;
    this->friction = 30.0f;
    this->resitution = .2f;
  };

};
