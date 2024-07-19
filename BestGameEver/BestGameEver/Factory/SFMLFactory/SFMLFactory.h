#pragma once
#include <SFML/Graphics.hpp>
#include "Types.h"

class Sprite : public sf::Sprite
{
public:
  float localRotation;
  flVec2 localTranslation;
};



class SFMLFactory
{
public:
  SFMLFactory();
  ~SFMLFactory();

  static Sprite * CreateSprite(std::string str, flVec2 size, flVec2 center, float angle);
};

