#pragma once
#include <vector>
#include "Types.h"
#include "Factory/PartFactory/UserParts.h"
#include "Factory/Box2DFactory/Box2DFactory.h"
#include "Factory/SFMLFactory/SFMLFactory.h"


class PartFactory
{
public:

  class Part;
  typedef std::vector<Part*> PartsBin;

  template <typename T>
  static Part * CreatePart(flVec2 size, flVec2 center, float rotation);

  class Part
  {
  public:
    b2FixtureDef * fixture = NULL;
    Sprite * sprite = NULL;
  };

  static b2Body * CreateBody(std::vector<Part*> parts, b2BodyType bodyType, std::string worldName);
  static std::vector<Sprite*>  GetSprites(std::vector<Part*> parts);

};

template <typename T>
PartFactory::Part * PartFactory::CreatePart(flVec2 size, flVec2 center, float rotation) {
  Part * part = new Part;
  T userCfg;
  flVec2 size_b(PIX_2_BOX(size.x), PIX_2_BOX(size.y));
  flVec2 center_b(PIX_2_BOX(center.x), PIX_2_BOX(center.y));

  if (userCfg.shape != NULL) {
    b2Shape * shape = userCfg.shape->GetShape(size_b, center_b, DEGREES_2_RAD(rotation));
    //TODO don't create body in all cases
    part->fixture = Box2DFactory::CreateFixture(shape, userCfg.material, size_b, center_b, DEGREES_2_RAD(rotation));

  }

  
  part->sprite = SFMLFactory::CreateSprite(userCfg.file, size, center, rotation);
  return part;
}


