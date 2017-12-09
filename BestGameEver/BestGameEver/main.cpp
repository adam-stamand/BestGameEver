#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"
#include <new> 
#include <string> 
#include <stdlib.h>
#include "SFML/Audio.hpp"


#include "Globals/Globals.h"
#include "Factory/Factory.h"
#include "UserComponents/UserComponents.h"
#include "Entity/Entity.h"
#include "Manager/Manager.h"


//figure out difference between at and [] for vectors

//consider changing itemType to partType

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
// make joint creator
// figure out how to apply initial rotation to sprites
// sensor collisions
// get center of mass working again // seems to be working... for the time being // generalize use
// use bullets
// decide character's velocity when exiting vehicle
// full screen gun doesn't work // decide how to scale game, or if you can
// make border maker
// create AI component
// Make a car //application of joints really
// Gun collides with walls first, causing it to move the joint // Consider masking it out, make uncollidable

typedef std::vector<Part*> Parts;



int main()
{
	//------------------------
	// Init
	//------------------------

	sf::RenderWindow window(sf::VideoMode(800, 600), "Best Game Ever", sf::Style::Default);
	sf::Clock deltaClock;
	sf::Music music;
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	if (!music.openFromFile(MUSIC(BestGameEverMaster.wav))) {
		return -1;
	}
	music.setLoop(true);
	//music.play();


	//------------------------
	// Create Items/Sprites
	//------------------------


	Parts borderParts{
		Factory::CreatePart<Border>(b2Vec2(SF_2_BOX(400),SF_2_BOX(300)),b2Vec2(SF_2_BOX(800),SF_2_BOX(600)))
	};
	Item * border = Factory::CreateItem(borderParts, STATIC_BODY);


	std::vector<Part*> rocketParts{
		Factory::CreatePart<Rocket>(b2Vec2(0,0), b2Vec2(1,2.5)),
		//Factory::CreatePart<Box>(b2Vec2(0,1), b2Vec2(2,2), DEGREES_2_RAD(45)),
		//Factory::CreatePart<Tire>(b2Vec2(0,-1), b2Vec2(1.5,1.5))
	};
	Item * rocket = Factory::CreateItem(rocketParts, DYNAMIC_BODY);
	rocket->body->SetAngularDamping(3);
	rocket->body->SetLinearDamping(0);
	rocket->body->SetTransform(b2Vec2(SF_2_BOX(200), SF_2_BOX(200)), 0);
	
	
	std::vector<Part*> characterParts{ 
		Factory::CreatePart<Character>(b2Vec2(0,0), b2Vec2(1,1)) 
	};
	Item * character = Factory::CreateItem(characterParts, DYNAMIC_BODY);
	character->body->SetTransform(b2Vec2(SF_2_BOX(400), SF_2_BOX(400)), 0);
	character->body->SetFixedRotation(true);
	
	
	std::vector<Part*> boxParts{ 
		Factory::CreatePart<Box>(b2Vec2(0,0), b2Vec2(2,2))
	};
	Item * box_body = Factory::CreateItem(boxParts, DYNAMIC_BODY);
	box_body->body->SetAngularDamping(2);
	box_body->body->SetTransform(b2Vec2(SF_2_BOX(300), SF_2_BOX(300)), DEGREES_2_RAD(0));




	Parts platformParts{
		Factory::CreatePart<Platform>(b2Vec2(0,0), b2Vec2(8,1))
	};
	Item * platform = Factory::CreateItem(platformParts, STATIC_BODY);
	platform->body->SetTransform(b2Vec2(SF_2_BOX(400), SF_2_BOX(200)), 0);




	
	std::vector<Part*> balloonParts{ 
		Factory::CreatePart<Balloon>(b2Vec2(0,0), b2Vec2(1,2))
	};
	Item * balloon = Factory::CreateItem(balloonParts, DYNAMIC_BODY);
	balloon->body->SetGravityScale(2);
	balloon->body->SetLinearDamping(1);
	balloon->body->SetAngularDamping(1);
	balloon->body->SetTransform(b2Vec2(SF_2_BOX(300), SF_2_BOX(300)), 0);
	//balloon->SetCenterMass(b2Vec2(0, -.5));


	std::vector<Part*> backgroundParts{
		Factory::CreatePart<Background>(b2Vec2(SF_2_BOX(400),SF_2_BOX(300)), b2Vec2(SF_2_BOX(800),SF_2_BOX(600)))
	};
	Item * background = Factory::CreateItem(backgroundParts);

	
	std::vector<Part*> gunParts{
		Factory::CreatePart<Cannon>(b2Vec2(0,0), b2Vec2(.35,1)),
	};
	Item * gun = Factory::CreateItem(gunParts, DYNAMIC_BODY);
	rocket->body->SetAngularDamping(3);
	rocket->body->SetLinearDamping(0);
	gun->body->SetTransform(b2Vec2(SF_2_BOX(200), SF_2_BOX(200)), 0);
	


	// Make unique config structs for each type of joint
	// then overload the create joint function using those structs
	b2RevoluteJointDef jointDef;
	jointDef.bodyA = gun->body;
	jointDef.bodyB = rocket->body;
	jointDef.collideConnected = false;
	jointDef.localAnchorA.Set(0, .2); 
	jointDef.localAnchorB.Set(0, -1);
	b2RevoluteJoint* m_joint = (b2RevoluteJoint*)Globals::world.CreateJoint(&jointDef);
	

	//------------------------
	// Create Entities
	//------------------------
	
	Entity background_ent;
	background_ent.Init(
	{
		new BasicGraphicsComponent(&window, background)
	}
	);

	EntityManager::RegisterEntity(&background_ent);




	Entity * trees[10];
	for (int i = 0; i < 10; i++) {

		Parts treeParts{
			Factory::CreatePart<Tree>(b2Vec2(SF_2_BOX((i * 100) + 50),SF_2_BOX(550)), b2Vec2(1,2))
		};
		Item * tree = Factory::CreateItem(treeParts);
		trees[i] = new Entity;
		trees[i]->Init(
		{
			new BasicGraphicsComponent(&window, tree)
		}
		);
		EntityManager::RegisterEntity(trees[i]);
	}



	Entity border_ent;
	border_ent.Init(
	{
		new BasicPhysicsComponent(border)
	}
	);
	border->body->SetUserData(&border_ent);
	EntityManager::RegisterEntity(&border_ent);


	Entity platform_ent;
	platform_ent.Init(
	{
		new BasicPhysicsComponent(platform),
		new BasicGraphicsComponent(&window, platform),
	}
	);
	platform->body->SetUserData(&platform_ent);
	EntityManager::RegisterEntity(&platform_ent);


	

	
	
	// Get better way to attach user data to bodies;
	
	Entity rocket_ent;
	rocket_ent.Init(
	{   
		new RocketControlsComponent(),
		new BasicGraphicsComponent(&window, rocket),
		new BasicPhysicsComponent(rocket) }
	);

	rocket->body->SetUserData(&rocket_ent);
	EntityManager::RegisterEntity(&rocket_ent);
	
	Entity gun_ent;
	gun_ent.Init(
	{
		new GunControlsComponent(),
		new BasicGraphicsComponent(&window, gun),
		new GunPhysicsComponent(gun, &window) }
	);

	gun->body->SetUserData(&gun_ent); //use entity id instead of reference
	EntityManager::RegisterEntity(&gun_ent);
	
	Entity character_ent;
	character_ent.Init(
	{ 
		  new BasicGraphicsComponent(&window, character),
		  new CharacterPhysicsComponent(character),
		  new CharacterControlsComponent() }
	);
	character->body->SetUserData(&character_ent);
	EntityManager::RegisterEntity(&character_ent);


	Entity balloon_ent;
	balloon_ent.Init(
	{
		new BasicGraphicsComponent(&window, balloon),
		new BasicPhysicsComponent(balloon) }
	);
	balloon->body->SetUserData(&balloon_ent);
	EntityManager::RegisterEntity(&balloon_ent);

	
	Entity box;
	box.Init(
	{ 
		new BasicGraphicsComponent(&window, box_body),
		new BasicPhysicsComponent(box_body) }
	);

	EntityManager::RegisterEntity(&box);

	
	Entity balloonConnect_ent;
	balloonConnect_ent.Init(
	{
		new ConnectionControlsComponent(),
		new BalloonConnectionComponent(balloon_ent.GetID(), character_ent.GetID()) }
	);
	EntityManager::RegisterEntity(&balloonConnect_ent);
	

	Entity connection_ent;
	connection_ent.Init(
	{
		new ConnectionControlsComponent(),
		new VehicleConnectionComponent(rocket_ent.GetID(), character_ent.GetID(), gun_ent.GetID()) }
	);
	
	EntityManager::RegisterEntity(&connection_ent);
	
	Entity temp_ent;
	temp_ent.Init(
	{
		new TempControlsComponent(),
		new GroundConnectionComponent(character_ent.GetID(), {platform_ent.GetID(), border_ent.GetID()}) }
	);

	EntityManager::RegisterEntity(&temp_ent);



	std::vector<Item*> rope;
	RevoluteJointConfig config;
	config.collide = false;


	for (int i = 0; i < 5; i++) {
		Parts * segmentParts = new Parts({
			Factory::CreatePart<Box>(b2Vec2(0,0),b2Vec2(.5,1.5)),
		});

		config.coordsA.push_back(b2Vec2(0,.75));
		config.coordsB.push_back(b2Vec2(0,-.75));

		Item * segment = Factory::CreateItem(*segmentParts, DYNAMIC_BODY);
		rope.push_back(segment);
		segment->body->SetTransform(b2Vec2(SF_2_BOX(300), SF_2_BOX(300)), 0);
		Entity * segment_ent = new Entity;
		segment_ent->Init(
		{
			new BasicGraphicsComponent(&window, segment),
			new BasicPhysicsComponent(segment) }
		);
		EntityManager::RegisterEntity(segment_ent);
	}

	config.coordsA.insert(config.coordsA.begin(), b2Vec2(0, 0));
	config.coordsB.insert(config.coordsB.begin(), b2Vec2(0, .75));
	rope.insert(rope.begin(), platform);
	Factory::CreateJoints(rope, config);
	
	ContactManager contactManager;
	contactManager.RegisterContact(&connection_ent);
	contactManager.RegisterContact(&temp_ent);
	contactManager.RegisterContact(&balloonConnect_ent);
	contactManager.RegisterFilter({rocket_ent.GetID(), character_ent.GetID(), gun_ent.GetID(), balloon_ent.GetID() });
	Globals::world.SetContactListener(&contactManager);

	
	//------------------------
	// Main Loop
	//------------------------

	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		window.clear();
		Globals::IncrTimer();
		EventManager::GetEvents(window);
		EntityManager::Update(window);
		Globals::world.Step(timeStep, velocityIterations, positionIterations);
		EventManager::ClearEvents();
		window.display();

	}

	return 0;
}
