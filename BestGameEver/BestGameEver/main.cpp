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


// GOALS
//
// Pop balloons
// Destory vehicle and character (health)
// Fuel for vehicle (inventory)
// Inventory for character
// Character hold on to balloon and float
// Make homing missle with splash damage


//TODO Character body still in game after entering vehicle

// let character jump
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

	// Define ground
	b2Vec2 groundBoxCoord[] = { b2Vec2(0,0),b2Vec2(800/30,0),b2Vec2(800/30,600/30),b2Vec2(0,600/30) };
	b2ChainShape groundChain;
	b2BodyDef groundBodyDef;
	b2FixtureDef groundFixtureDef;
	b2Body* groundBody;

	groundChain.CreateLoop(groundBoxCoord, 4);
	groundBodyDef.type = b2_staticBody;
	groundBodyDef.position.Set(0, 0);
	groundFixtureDef.shape = &groundChain;
	groundBody = Globals::world.CreateBody(&groundBodyDef);
	groundBody->CreateFixture(&groundFixtureDef);







	
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
	Item * background = Factory::CreateItem(backgroundParts, DYNAMIC_BODY);

	
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

	
	
	Entity * trees[5];
	for (int i = 0; i < 10; i++) {
		
		std::vector<Part*> treeParts{
			Factory::CreatePart<Tree>(b2Vec2(SF_2_BOX((i*100) + 50),SF_2_BOX(550)), b2Vec2(1,2))
		};
		Item * tree = Factory::CreateItem(treeParts, DYNAMIC_BODY);
		trees[i] = new Entity;
		trees[i]->Init(
		{
			new BasicGraphicsComponent(&window, tree)
		}
		);
		EntityManager::RegisterEntity(trees[i]);
	}
	
	
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
	

	
	ContactManager contactManager;
	contactManager.RegisterContact(&connection_ent);
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
