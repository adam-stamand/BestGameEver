#pragma once
#include "Box2d/Box2d.h"
#include <map>
#include <string.h>

class Box2DManager
{
public:
  Box2DManager();
  ~Box2DManager();




  static b2World * RemoveWorld(std::string name);
  static void AddWorld(std::string name, b2World * world);
  static int GetWorld(std::string name, b2World * &world);
  static std::map<std::string, b2World*>::const_iterator worlds_begin();
  static std::map<std::string, b2World*>::const_iterator worlds_end();



private:
  static std::map<std::string, b2World*> worldMap;

};

