

#include <new> 
#include <string> 
#include <stdlib.h>


#include "Utils/Timer.h"

#include "FWInterface/FWInterface.h"
#include "Factory/Factory.h"
#include "UserComponents/UserComponents.h"
#include "Manager/Manager.h"


// create fl namespace


// Takeaways 
// - InterEntity: pull out controls to central class/manager. Create connection manager, use it to register wtih contact manager; Still have connection components
// Connection manager takes registration; has methods like InCtonactWith, and GetPairedEntity. Connection manager registers with contact manager
// - IntraEntity: Messaging, create base messaging class, create specific message classes (in a library). Use strings as names for referencing message type.
// - Entity Creation: Create heirarchy of user components, such that controls conpoments can know about other types. // Scratch that
// Make spawn component that can spawn other entities. Create interface for attaching spawn entiteis, if needed, but make entity library all the same and
// make it easy for everyone else to create entities.




//multiple windows; consider

// make some way to check entity has been reigstered before refereing
//figure out difference between at and [] for vectors

//consider changing itemType to partType


// Get better way to attach user data to bodies;



// GOALS
//
// Pop balloons
// Destory vehicle and character (health)
// Fuel for vehicle (inventory)
// Inventory for character
// Character hold on to balloon and float
// Make homing missle with splash damage


//TODO Character body still in game after entering vehicle

// Create debugging setup, so that asserts tell useful info
// let character jump // on all object, not just ground
// sensor collisions
// get center of mass working again // seems to be working... for the time being // generalize use
// use bullets
// decide character's velocity when exiting vehicle
// full screen gun doesn't work // decide how to scale game, or if you can
// create AI component
// Gun collides with walls first, causing it to move the joint // Consider masking it out, make uncollidable





int main()
{

  //SFMLManager::PlayBackgroundMusic(MUSIC(BestGameEverMaster.wav));

	//------------------------
	// Create Entites/Items
	//------------------------
  EntityManager Manager("Manager");
  Entity Characters("Characters");
  Entity Level("Level");
  Entity Borders("Borders");
  Entity Player("Player");

  Manager.AddEntity(&Characters);
  Manager.AddEntity(&Level);

  Characters.AddEntity(&Player);
  Level.AddEntity(&Borders);


  ItemFactory::Item item;


  // TODO Rename Border to Border_t and all others

  item.Build(
  {
    ItemFactory::CreatePart<Border>(flVec2(800,600), flVec2(400,300), 0),
  }, STATIC_BODY, "init");

  Borders.AddComponents({
    new BasicPhysicsComponent("BorderPhysics", item.body),
  });


  item.Build(
  {
    ItemFactory::CreatePart<Rocket>(flVec2(30,70), flVec2(0,0), 0),
    ItemFactory::CreatePart<Tire>(flVec2(30,30), flVec2(0,30), 45), //TODO sprite drawing is fucked here
    //ItemFactory::CreatePart<Box>(flVec2(30,30), flVec2(200,200), 0),
  }, DYNAMIC_BODY, "init");

  //TODO add to item interface?
  item.body->SetTransform(flVec2(PIX_2_BOX(400), PIX_2_BOX(300)), 0);
  item.body->SetGravityScale(1);

  Player.AddComponents({
    new BasicPhysicsComponent("Physics", item.body),
    new BasicControlsComponent("Controls"),
    new BasicGraphicsComponent("Graphics", item.sprites)
  });


  /*

  


	Entity background_ent("Background"); Item* background = 0;
	MakeBackground(background_ent,& background);

	Entity platform_ent("Platform_Ent"); Item *platform = 0;
	MakePlatform(platform_ent, &platform);
	Entity tree_ent[10]; Item *tree[10];
	for (int i = 0; i < 10; i++) {
		MakeTree(tree_ent[i], &tree[i]);
	}

	Entity character_ent("Character_Ent"); Item * character = 0;
	MakeCharacter(character_ent, &character);

	Entity border_ent("Border_Ent"); Item *border = 0;
	MakeBorder(border_ent, &border);

	Entity balloon_ent("Balloon_Ent"); Item* balloon;
	MakeBalloon(balloon_ent, &balloon);
	
	Entity rocket_ent("Rocket_Ent"); Item *rocket = 0;
	MakeRocket(rocket_ent, &rocket);

	Entity gun_ent("Gunt_Ent"); Item *gun=0;
	MakeGun(gun_ent, &gun);	

	Entity car_ent("Car_ent"); Item *car = 0;
	MakeCar(car_ent, &car);

	Entity wheel1_ent; Item *wheel1 = 0;
	MakeWheel1(wheel1_ent, &wheel1);

	Entity wheel2_ent; Item *wheel2 = 0;
	MakeWheel2(wheel2_ent, &wheel2);
	
	Entity stringSegs[5]; Item *balloonStrings[5]; std::vector<Item*> balloonString;
	for (int i = 0; i < 5; i++) {
		MakeString(stringSegs[i], &balloonStrings[i]);
		balloonString.push_back(balloonStrings[i]);
	}

	Entity ropeSegs[5]; Item *ropeArray[5]; std::vector<Item*> rope;
	for (int i = 0; i < 5; i++) {
		MakeRope(ropeSegs[i], &ropeArray[i]);
		rope.push_back(ropeArray[i]);
	}

	std::vector<uint32_t> tempVec;
	tempVec.resize(CharacterConnectionComponent::NUM_CONNECTION);
	tempVec[CharacterConnectionComponent::BALLOON_CONNECTION] = balloon_ent.GetID();
	tempVec[CharacterConnectionComponent::ROCKET_CONNECTION] = rocket_ent.GetID();
	tempVec[CharacterConnectionComponent::GUN_CONNECTION] = gun_ent.GetID();
	tempVec[CharacterConnectionComponent::CAR_CONNECTION] = car_ent.GetID();
	tempVec[CharacterConnectionComponent::SEGMENT_CONNECTION] = stringSegs[4].GetID();
	character_ent.AddComponent({ new CharacterConnectionComponent(tempVec) });

	//------------------------
	// Create Joints
	//------------------------


	RevoluteJointConfig stringConfig;
	stringConfig.collide = false;
	for (int i = 0; i < 4; i++) {
		stringConfig.coordsA.push_back(b2Vec2(0, .25));
		stringConfig.coordsB.push_back(b2Vec2(0, -.25));
	}
	stringConfig.coordsA.insert(stringConfig.coordsA.begin(), b2Vec2(0, .25));
	stringConfig.coordsB.insert(stringConfig.coordsB.begin(), b2Vec2(0, -.25));
	balloonString.insert(balloonString.begin(), balloon);
	Factory::CreateJoints(balloonString, stringConfig);
	

	RevoluteJointConfig config;
	config.collide = false;
	for (int i = 0; i < 4; i++) {
		config.coordsA.push_back(b2Vec2(0, .75));
		config.coordsB.push_back(b2Vec2(0, -.75));
	}
	config.coordsA.insert(config.coordsA.begin(), b2Vec2(0, .25));
	config.coordsB.insert(config.coordsB.begin(), b2Vec2(0, -.75));
	rope.insert(rope.begin(), platform);
	Factory::CreateJoints(rope, config);
	
	
	RevoluteJointConfig rocketConfig;
	rocketConfig.collide = false;
	rocketConfig.coordsA.push_back(b2Vec2(0,-1));
	rocketConfig.coordsB.push_back(b2Vec2(0,.25));
	Factory::CreateJoints({ rocket, gun}, rocketConfig);


	WheelJointConfig wheelConfig;
	wheelConfig.collide = false;
	wheelConfig.axis = b2Vec2(0, 1);
	wheelConfig.coordsA = b2Vec2(-1.5, 1.5);
	wheelConfig.coordsB = b2Vec2(0, 0);
	Factory::CreateJoints(car, wheel1, wheelConfig);
	wheelConfig.coordsA = b2Vec2(1.5, 1.5);
	Factory::CreateJoints(car, wheel2, wheelConfig);




	//------------------------
	// Create Connections
	//------------------------
	
	/*
	Entity connection_ent;
	connection_ent.Init(
	{
		new ConnectionControlsComponent(),
		new VehicleConnectionComponent(rocket_ent->GetID(), character_ent->GetID(), gun_ent->GetID()) }
	);
	
	EntityManager::RegisterEntity(&connection_ent);
	
	Entity temp_ent;
	temp_ent.Init(
	{
		new TempControlsComponent(),
		new GroundConnectionComponent(character_ent->GetID(), {platform_ent->GetID(), border_ent->GetID()}) }
	);
	EntityManager::RegisterEntity(&temp_ent);
	
	

	
	Entity balloonConnect_ent;
	balloonConnect_ent.Init(
	{
		new ConnectionControlsComponent(), 
		new BalloonConnectionComponent(balloon_ent->GetID(), character_ent->GetID(), stringSegs[4]->GetID()) }
	);
	EntityManager::RegisterEntity(&balloonConnect_ent);
	
	

	Entity carConnect_ent;
	carConnect_ent.Init(
	{
		new ConnectionControlsComponent(), 
		new VehicleConnectionComponent(car_ent->GetID(), character_ent->GetID(), gun_ent->GetID())}
	);

	EntityManager::RegisterEntity(&carConnect_ent);
	
	*/
	
	//------------------------
	// Main Loop
	//------------------------


	for (auto iter = SFMLManager::windows_begin(); iter != SFMLManager::windows_end(); iter++) {
     iter->second->setFramerateLimit(60);
  }

  float32 timeStep = 1.0f / 60.0f;
  int32 velocityIterations = 6;
  int32 positionIterations = 2;

  while (1) {


    for (auto iter = SFMLManager::windows_begin(); iter != SFMLManager::windows_end(); iter++)
    {
      sf::RenderWindow * window = iter->second;
      SFMLManager::GetEvents(window);
      SFMLManager::ClearEvents();
      window->clear();
    }




    Timer::IncrTimer();
    Manager.Update();

    for (auto iter = SFMLManager::windows_begin(); iter != SFMLManager::windows_end(); iter++) 
    {
      sf::RenderWindow * window = iter->second;
      window->display();  
    }

    for (auto iter = Box2DManager::worlds_begin(); iter != Box2DManager::worlds_end(); iter++)
    {
      b2World * world = iter->second;
      world->Step(timeStep, velocityIterations, positionIterations);
    }


  }

	return 0;
}


