#pragma once
#include <vector>
#include "Types.h"
#include "Factory/ItemFactory/UserItems.h"
#include "Factory/Box2DFactory/Box2DFactory.h"
#include "Factory/SFMLFactory/SFMLFactory.h"


class ItemFactory
{
public:
  ItemFactory();
  ~ItemFactory();
  class Part;
  class Item;


  template <typename T>
  static Part * CreatePart(flVec2 size, flVec2 center, float rotation);



  class Item
  {
  public:
    Item() {};

    void Build(std::vector<Part*> parts, b2BodyType bodyType, std::string worldName);
    std::vector<Sprite*> sprites;
    b2Body * body;
  };



  class Part
  {
  public:
    b2FixtureDef * fixture;
    Sprite * sprite;
  };

};

template <typename T>
ItemFactory::Part * ItemFactory::CreatePart(flVec2 size, flVec2 center, float rotation) {
  Part * part = new Part;
  T userCfg;
  flVec2 size_b(PIX_2_BOX(size.x), PIX_2_BOX(size.y));
  flVec2 center_b(PIX_2_BOX(center.x), PIX_2_BOX(center.y));

  b2Shape * shape = userCfg.shape->GetShape(size_b, center_b, DEGREES_2_RAD(rotation));
  //TODO don't create body in all cases
  part->fixture = Box2DFactory::CreateFixture(shape,userCfg.material, size_b, center_b, DEGREES_2_RAD(rotation));
  //TODO don't create sprite in all cases
  part->sprite = SFMLFactory::CreateSprite(userCfg.file, size, center, rotation);
  return part;
}


