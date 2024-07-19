#include "SFMLFactory.h"



SFMLFactory::SFMLFactory()
{
}


SFMLFactory::~SFMLFactory()
{
}




Sprite * SFMLFactory::CreateSprite(std::string str, flVec2 size, flVec2 center, float angle) {
  Sprite * sprite = new Sprite;
  sf::Texture * texture = new sf::Texture;
  texture->loadFromFile(str);
  sprite->setTexture(*texture);
  float currX, currY, scaleX, scaleY;
  currX = (float)texture->getSize().x;
  currY = (float)texture->getSize().y;

  scaleX = size.x / currX;
  scaleY = size.y / currY;

  sprite->setScale(scaleX, scaleY);
  // setOrigin is done in original Sprite coordinates! (before scaling)
  sprite->setOrigin(currX / 2, currY / 2);
  sprite->localRotation = angle;
  sprite->localTranslation = center;
  return sprite;
}
