#pragma once
#include "BloxFW/BloxFW.h"
#include "Factory/Box2DFactory/Box2DFactory.h"
#include "Types.h"

class VectorMessage : public bx::Message
{
public:
  float magnitude;
  flVec2 unitVec;
  flVec2 point;
};

class TransformMessage : public bx::Message
{
public:
  float rotation;
  flVec2 translation;
};

class BodyMessage : public bx::Message
{
public:
  b2Body * body;
};

class RevoluteJointMessage : public  bx::Message
{
public:
  RevoluteJointConfig cfg;
  std::string name;
};
