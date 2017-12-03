#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"
#include <new> 
#include <string> 
#include <stdlib.h>
#include "SFML/Audio.hpp"


#include "Globals/Globals.h"
#include "Factory/Factory.h"
#include "Entity/Entity.h"
#include "Components/Components.h"
#include "Level/EventHandler.h"
#include "Level/EntityManager.h"
#include "Level/ContactManager.h"


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
// use bullets


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

	uint16_t mask = 0xFFFD;
	uint16_t category = 0x0004;
	std::vector<ItemFixture*> rocketFixtures{
		Factory::CreateItemFixture<Rocket>(b2Vec2(0,0), b2Vec2(1,2.5),0, mask, category),
		//Factory::CreateItemFixture<Cannon>(b2Vec2(0,-1.1), b2Vec2(1,1), 90, mask, category),
		//Factory::CreateItemFixture<Tire>(b2Vec2(0,1), b2Vec2(1,1), 0, mask, category),
		//Factory::CreateItemFixture<Tire>(b2Vec2(-.5,0), b2Vec2(1,1), 0, mask, category),
		//Factory::CreateItemFixture<Tire>(b2Vec2(.5,0), b2Vec2(1,1), 0, mask, category)
	};
	Item * rocket = Factory::CreateItem(rocketFixtures, DYNAMIC_BODY);
	rocket->body->SetAngularDamping(3);
	rocket->body->SetLinearDamping(0);
	rocket->body->SetTransform(b2Vec2(200 / WORLD_SCALE, 200 / WORLD_SCALE), 0);
	


	mask = 0xFFFF;// 0xFFFB;
	category = 0x1;// 0x0002;
	std::vector<ItemFixture*> characterFixtures{ Factory::CreateItemFixture<Character>(b2Vec2(0,0), b2Vec2(2,2),0, mask, category) };
	Item * character = Factory::CreateItem(characterFixtures, DYNAMIC_BODY);
	character->body->SetTransform(b2Vec2(400 / WORLD_SCALE, 400 / WORLD_SCALE), 0);
	character->body->SetFixedRotation(true);
	

	
	std::vector<ItemFixture*> balloonFixtures{ Factory::CreateItemFixture<Balloon>(b2Vec2(0,0), b2Vec2(1,2)) };
	Item * balloon = Factory::CreateItem(balloonFixtures, DYNAMIC_BODY);
	balloon->body->SetGravityScale(-.5);
	balloon->body->SetLinearDamping(3);
	balloon->body->SetAngularDamping(1);
	balloon->body->SetTransform(b2Vec2(300 / WORLD_SCALE, 300 / WORLD_SCALE), 0);
	//b2MassData massD;
	//balloon->body->GetMassData(&massD);
	//massD.center.Set(0, -0.5);
	//balloon->body->SetMassData(&massD);


	sf::Sprite * tree = Factory::CreateSprite(IMAGE(tree.png), BOX_2_SF(2), BOX_2_SF(4), b2Vec2(0,0));
	sf::Sprite * background = Factory::CreateSprite(IMAGE(sky_background.png), 800, 600, b2Vec2(0, 0));



	std::vector<ItemFixture*> gunFixtures{
		Factory::CreateItemFixture<Cannon>(b2Vec2(0,0), b2Vec2(.35,1), 0, mask, category),
	};
	Item * gun = Factory::CreateItem(gunFixtures, DYNAMIC_BODY);
	rocket->body->SetAngularDamping(3);
	rocket->body->SetLinearDamping(0);
	gun->body->SetTransform(b2Vec2(200 / WORLD_SCALE, 200 / WORLD_SCALE), 0);



	
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


	/*
	Entity background_ent(
	{ new BasicGraphicsComponent(&window, {background}),
			new BackgroundPhysicsComponent(NULL, SF_2_BOX(400),SF_2_BOX(300)) }
	);

	EntityManager::RegisterEntity(&background_ent);



	Entity * trees[5];
	for (int i = 0; i < 5; i++) {
		trees[i] = new Entity(
		{ new BasicGraphicsComponent(&window, {tree}),
			  new BackgroundPhysicsComponent(NULL,SF_2_BOX(i*150.0 + 100.0), SF_2_BOX(525.0))}
		);
		EntityManager::RegisterEntity(trees[i]);
	}
	*/



	Entity main_ent(
	{ new RocketControlsComponent(),
		new BasicGraphicsComponent(&window, rocket->itemFixtures),
		new RocketPhysicsComponent(rocket->body) }
	);
	rocket->body->SetUserData(&main_ent);

	EntityManager::RegisterEntity(&main_ent);
	
	Entity gun_ent(
	{
		new GunControlsComponent(),
		new BasicGraphicsComponent(&window, gun->itemFixtures),
		new GunPhysicsComponent(gun->body, &window)
	}
	);

	gun->body->SetUserData(&gun_ent);
	EntityManager::RegisterEntity(&gun_ent);
	



	Entity character_ent(
		{ 
		  new BasicGraphicsComponent(&window, character->itemFixtures),
		  new CharacterPhysicsComponent(character->body),
		  new CharacterControlsComponent() }
	);

	character->body->SetUserData(&character_ent);
	EntityManager::RegisterEntity(&character_ent);




	Entity balloon_ent(
		{new BasicGraphicsComponent(&window, balloon->itemFixtures),
		 new BasicPhysicsComponent(balloon->body)}
	);
	balloon->body->SetUserData(&balloon_ent);
	EntityManager::RegisterEntity(&balloon_ent);




	/*
	Entity * boxes[6];
	Item * boxes_body[6];
	for (int i = 0; i < 6; i++) {
	boxes_body[i] = Factory::CreateItem<Box>(BOX_2_SF(1), BOX_2_SF(1));
	boxes_body[i]->body->SetAngularDamping(2);
	boxes_body[i]->body->SetTransform(b2Vec2(300 / WORLD_SCALE, 300 / WORLD_SCALE), DEGREES_2_RAD(40));

	boxes[i] = new 	Entity(
	{ new BasicGraphicsComponent(&window, boxes_body[i]->sprites),
	new BasicPhysicsComponent(boxes_body[i]->body) }
	);

	EntityManager::RegisterEntity(boxes[i]);

	}
	*/
	
	Entity * box;
	Item * box_body;
	std::vector<ItemFixture*> boxFixtures{ Factory::CreateItemFixture<Box>(b2Vec2(0,0), b2Vec2(1,1)) };
	box_body = Factory::CreateItem(boxFixtures, DYNAMIC_BODY);
	box_body->body->SetAngularDamping(2);
	box_body->body->SetTransform(b2Vec2(300 / WORLD_SCALE, 300 / WORLD_SCALE), DEGREES_2_RAD(40));

	box = new 	Entity(
	{ new BasicGraphicsComponent(&window, box_body->itemFixtures),
		new BasicPhysicsComponent(box_body->body) }
	);

	box_body->body->SetUserData(&box);
	EntityManager::RegisterEntity(box);

	

	
	
	Entity connection_ent(
	{
		new ConnectionControlsComponent(),
		new VehicleConnectionComponent(&main_ent, &character_ent, &gun_ent)
	}
	);
	EntityManager::RegisterEntity(&connection_ent);
	

	
	ContactManager contactManager;
	contactManager.RegisterContact(&connection_ent);
	contactManager.RegisterFilter({main_ent.id, character_ent.id, gun_ent.id});
	Globals::world.SetContactListener(&contactManager);


	//------------------------
	// Main Loop
	//------------------------

	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		window.clear();
		Globals::IncrTimer();
		EventHandler::GetEvents(window);
		EntityManager::Update(window);
		Globals::world.Step(timeStep, velocityIterations, positionIterations);
		EventHandler::ClearEvents();
		window.display();

	}

	return 0;
}
