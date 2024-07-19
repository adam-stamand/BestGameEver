#include "Box2DManager.h"



Box2DManager::Box2DManager()
{
}


Box2DManager::~Box2DManager()
{
}


std::map<std::string, b2World*> Box2DManager::worldMap = { {"init", new b2World(b2Vec2(0.0, 4.0)) } };


void Box2DManager::RemoveWorld(std::string name) {
  auto iter = worldMap.erase(name);
}


int Box2DManager::GetWorld(std::string name, b2World *&World) {
  auto iter = worldMap.find(name);
  if (iter == worldMap.end()) {
    assert(0);
    return -1;
  }
  World = iter->second;
  return 0;
}



void Box2DManager::AddWorld(std::string name, b2World * World) {
  worldMap.insert(std::pair<std::string, b2World*>(name, World));
}


std::map<std::string, b2World*>::const_iterator Box2DManager::worlds_begin() {
  return Box2DManager::worldMap.begin();
}

std::map<std::string, b2World*>::const_iterator Box2DManager::worlds_end() {
  return Box2DManager::worldMap.end();
}
