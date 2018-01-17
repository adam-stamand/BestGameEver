#pragma once
#include "BloxFW/BloxFW.h"
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