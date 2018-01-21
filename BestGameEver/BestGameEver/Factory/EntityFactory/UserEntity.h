#pragma once

#include "Factory/PartFactory/PartFactory.h"
#include "UserComponents/UserComponents.h"




class Entity_t
{

public:
  std::vector<Component*> components;
  PartFactory::Part Part;
};


class Tree_ent : public Entity_t
{
public:
  Tree_ent() {
    PartFactory::PartsBin bin =  
    {
      PartFactory::CreatePart<Tree_t>(flVec2(30,70), flVec2(0,0), 0),
    };

    std::vector<Sprite*> sprites = PartFactory::GetSprites(bin);

    components = {
      new BackgroundGraphicsComponent("Graphics", sprites)
    };
  }
};



class Border_ent : public Entity_t
{
public:
  Border_ent() {
    PartFactory::PartsBin bin =
    {
      PartFactory::CreatePart<Border_t>(flVec2(800,600), flVec2(400,300), 0),
    };

    b2Body * body = PartFactory::CreateBody(bin, STATIC_BODY, "init");

    components = {
      new BasicPhysicsComponent("BorderPhysics", body),
    };
  }
};




class Box_ent : public Entity_t
{
public:
  Box_ent() {
    PartFactory::PartsBin bin =
    {
      PartFactory::CreatePart<Box_t>(flVec2(30,30), flVec2(0,0), 0),
    };

    std::vector<Sprite*> sprites = PartFactory::GetSprites(bin);
    b2Body * body = PartFactory::CreateBody(bin, DYNAMIC_BODY, "init");

    body->SetTransform(flVec2(PIX_2_BOX(200), PIX_2_BOX(100)), 0);

    components = {
      new BasicPhysicsComponent("Physics", body),
      new BasicGraphicsComponent("Graphics", sprites)
    };
  }
};


class Rocket_ent : public Entity_t
{
public:
  Rocket_ent() {
    PartFactory::PartsBin bin =
    {
      PartFactory::CreatePart<Rocket_t>(flVec2(30,70), flVec2(0,0), 0)
    };

    std::vector<Sprite*> sprites = PartFactory::GetSprites(bin);
    b2Body * body = PartFactory::CreateBody(bin, DYNAMIC_BODY, "init");

    body->SetTransform(flVec2(PIX_2_BOX(200), PIX_2_BOX(300)), 0);

    components = {
      new BasicPhysicsComponent("Physics", body),
      new RocketControlsComponent("Controls"),
      new BasicGraphicsComponent("Graphics", sprites)
    };
  }

};



class Background_ent : public Entity_t
{
public:
  Background_ent() {
    PartFactory::PartsBin bin =
    {
      PartFactory::CreatePart<Background_t>(flVec2(800,600), flVec2(0,0), 0),
    };

    std::vector<Sprite*> sprites = PartFactory::GetSprites(bin);
    
    components = {
      new BackgroundGraphicsComponent("Graphics", sprites)
    };
  }

};


class Platform_ent : public Entity_t
{
public:
  Platform_ent() {
    PartFactory::PartsBin bin =
    {
      PartFactory::CreatePart<Platform_t>(flVec2(200,20), flVec2(0,0), 0),
    };

    std::vector<Sprite*> sprites = PartFactory::GetSprites(bin);
    b2Body * body = PartFactory::CreateBody(bin, STATIC_BODY, "init");

    body->SetTransform(flVec2(PIX_2_BOX(400), PIX_2_BOX(200)), 0);
    
    components = {
      new BasicGraphicsComponent("Graphics", sprites),
      new BasicPhysicsComponent("Physics", body)
    };
  }

};

class Balloon_ent : public Entity_t
{
public:
  Balloon_ent() {
    PartFactory::PartsBin bin =
    {
      PartFactory::CreatePart<Balloon_t>(flVec2(30,50), flVec2(0,0), 0),
    };

    std::vector<Sprite*> sprites = PartFactory::GetSprites(bin);
    b2Body * body = PartFactory::CreateBody(bin, DYNAMIC_BODY, "init");

    body->SetTransform(flVec2(PIX_2_BOX(200), PIX_2_BOX(300)), 0);

    components = {
      new BasicGraphicsComponent("Graphics", sprites),
      new BasicPhysicsComponent("Physics", body)
    };
  }

};


class Rope_ent : public Entity_t
{
public:
  Rope_ent() {
    PartFactory::PartsBin bin =
    {
      PartFactory::CreatePart<Rope_t>(flVec2(15,4), flVec2(0,0), 0),
    };

    std::vector<Sprite*> sprites = PartFactory::GetSprites(bin);
    b2Body * body = PartFactory::CreateBody(bin, DYNAMIC_BODY, "init");

    components = {
      new BasicGraphicsComponent("Graphics", sprites),
      new BasicPhysicsComponent("Physics", body)
    };
  }

};


class Player_ent : public Entity_t
{
public:
  Player_ent() {
    PartFactory::PartsBin bin =
    {
      PartFactory::CreatePart<Character_t>(flVec2(25,25), flVec2(0,0), 0),
    };

    std::vector<Sprite*> sprites = PartFactory::GetSprites(bin);
    b2Body * body = PartFactory::CreateBody(bin, DYNAMIC_BODY, "init");
    body->SetFixedRotation(true);

    components = {
      new BasicGraphicsComponent("Graphics", sprites),
      new BasicPhysicsComponent("Physics", body),
      new CharacterControlsComponent("Controls")
    };
  }

};



class Cannon_ent : public Entity_t
{
public:
  Cannon_ent() {
    PartFactory::PartsBin bin =
    {
      PartFactory::CreatePart<Cannon_t>(flVec2(10,25), flVec2(0,0), 0),
    };

    std::vector<Sprite*> sprites = PartFactory::GetSprites(bin);
    b2Body * body = PartFactory::CreateBody(bin, DYNAMIC_BODY, "init");

    components = {
      new BasicGraphicsComponent("Graphics", sprites),
      new BasicPhysicsComponent("Physics", body),
      new GunControlsComponent("Controls")
    };
  }

};