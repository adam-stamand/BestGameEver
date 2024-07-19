#include "Factory/PartFactory/PartFactory.h"




b2Body * PartFactory::CreateBody(std::vector<Part*> parts, b2BodyType bodyType, std::string worldName) {

  std::vector<b2FixtureDef*> fixtures;

  for (unsigned int i = 0; i < parts.size(); i++) {
    b2FixtureDef * fixture = parts.at(i)->fixture;
    fixtures.push_back(fixture);
  }

  return Box2DFactory::CreateBody(fixtures, bodyType, worldName);
}


std::vector<Sprite*>  PartFactory::GetSprites(std::vector<Part*> parts) {
  std::vector<Sprite*> sprites;
  for (unsigned int i = 0; i < parts.size(); i++) {
    sprites.push_back(parts.at(i)->sprite);
  }
  return sprites;
}