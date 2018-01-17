#include "Factory/ItemFactory/ItemFactory.h"



ItemFactory::ItemFactory()
{
}


ItemFactory::~ItemFactory()
{
}



void ItemFactory::Item::Build(std::vector<Part*> parts, b2BodyType bodyType, std::string worldName) { // needs world name

  std::vector<b2FixtureDef*> fixtures;
  sprites.clear();
  body = NULL;

  for (unsigned int i = 0; i < parts.size(); i++) {
    fixtures.push_back(parts.at(i)->fixture);
    Sprite * sprite = parts.at(i)->sprite;

    if (sprite != NULL) {
      sprites.push_back(sprite);
    }
    delete(parts.at(i));
  }
  //TODO; don't necessarily make a body
  body = Box2DFactory::CreateBody(fixtures, bodyType, worldName);
}