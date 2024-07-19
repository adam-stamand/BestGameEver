#pragma once


#include "BaseComponents/SFMLGraphics/SFMLGraphicsComponent.h"
#include "BaseComponents/Message.h"

class BackgroundGraphicsComponent : public SFMLGraphicsComponent
{
public:
  BackgroundGraphicsComponent(std::string name, std::vector<Sprite*> sprites, std::string windowName = "init") : SFMLGraphicsComponent(name, sprites, windowName) {};
  ~BackgroundGraphicsComponent() {};


  void BackgroundGraphicsComponent::Init() {
    SubscribeMessage(&BackgroundGraphicsComponent::GetTransform, "GetTransform");
    SubscribeMessage(&BackgroundGraphicsComponent::SetTransform, "SetTransform");

  }

  void BackgroundGraphicsComponent::GetTransform(bx::Message &msg) {
    TransformMessage *trans = static_cast<TransformMessage*>(&msg);
    trans->rotation = backgroundRotation;
    trans->translation = backgroundTranslation;
  }

  void BackgroundGraphicsComponent::SetTransform(bx::Message &msg) {
    TransformMessage *trans = static_cast<TransformMessage*>(&msg);
    backgroundRotation = trans->rotation;
    backgroundTranslation = trans->translation;
  }


  float backgroundRotation = 0;
  flVec2 backgroundTranslation = flVec2(0,0);

};

