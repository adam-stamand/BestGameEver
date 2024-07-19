#pragma once

#include "FWInterface/Component.h"
#include "BaseComponents/Message.h"

class FLBaseComponent : public Component
{
public:
  FLBaseComponent(std::string name) : Component(name) {}
  ~FLBaseComponent() {}

  void Update() {};
};
