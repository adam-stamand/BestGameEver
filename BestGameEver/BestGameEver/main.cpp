#include <SFML/Graphics.hpp>
#include <new> 
#include "Box2D/Box2D.h"
#include <string> 
#include <stdlib.h>
#include "SFML/Audio.hpp"


#include "Globals/Globals.h"
#include "Factory/Factory.h"
#include "Entity/Entity.h"
#include "Components/Components.h"
#include "Level/EventHandler.h"
#include "Level/EntityManager.h"

//TODO Character body still in game after entering vehicle


// use joints
// use multiple fixtures; one body
// sensor collisions
// fix persistent character body
// use bullets
// enter ship only within distance
// no collision between character and ship


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
	Item * rocket = Factory::CreateItem<Rocket>(BOX_2_SF(1), BOX_2_SF(2), mask, category);
	rocket->body->SetAngularDamping(3);
	rocket->body->SetLinearDamping(0);
	rocket->body->SetTransform(b2Vec2(200 / WORLD_SCALE, 200 / WORLD_SCALE), 0);
	//rocket->body->SetGravityScale(0);

	mask = 0xFFFB;
	category = 0x0002;
	Item * character = Factory::CreateItem<Character>(BOX_2_SF(1), BOX_2_SF(1), mask, category);
	character->body->SetTransform(b2Vec2(400 / WORLD_SCALE, 400 / WORLD_SCALE), 0);
	character->body->SetFixedRotation(true);
	


	Item * balloon = Factory::CreateItem<Balloon>(BOX_2_SF(1), BOX_2_SF(2));
	balloon->body->SetGravityScale(-.5);
	balloon->body->SetLinearDamping(3);
	balloon->body->SetAngularDamping(1);
	balloon->body->SetTransform(b2Vec2(300 / WORLD_SCALE, 300 / WORLD_SCALE), 0);
	
	b2MassData massD;
	balloon->body->GetMassData(&massD);
	massD.center.Set(0, -0.5);
	balloon->body->SetMassData(&massD);


	sf::Sprite * tree = Factory::CreateSprite(IMAGE(tree.png), BOX_2_SF(2), BOX_2_SF(4));
	sf::Sprite * background = Factory::CreateSprite(IMAGE(sky_background.png), 800, 600);


	//------------------------
	// Create Entities
	//------------------------



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


	Entity main_ent(
	{ new RocketControlsComponent(),
		new BasicGraphicsComponent(&window, rocket->sprites),
		new RocketPhysicsComponent(rocket->body) }
	);


	EntityManager::RegisterEntity(&main_ent);



	Entity character_ent(
		{ 
		  new BasicGraphicsComponent(&window, character->sprites),
		  new CharacterPhysicsComponent(character->body),
		  new CharacterControlsComponent() }
	);

	EntityManager::RegisterEntity(&character_ent);


	Entity lvl_ent(
		{ new LevelControlsComponent(&main_ent, &character_ent)}
	);


	EntityManager::RegisterEntity(&lvl_ent);

	Entity balloon_ent(
		{new BasicGraphicsComponent(&window, balloon->sprites),
		 new BasicPhysicsComponent(balloon->body)}
	);
	EntityManager::RegisterEntity(&balloon_ent);




	/*
	Entity * boxes[6];
	Item * boxes_body[6];
	for (int i = 0; i < 6; i++) {
	boxes_body[i] = Factory::CreateItem<Box>(BOX_2_SF(1), BOX_2_SF(1));
	boxes_body[i]->body->SetAngularDamping(2);
	boxes_body[i]->body->SetTransform(b2Vec2(300 / WORLD_SCALE, 300 / WORLD_SCALE), DEGREES_2_RAD(40));

	boxes[i] = new 	Entity(
	{ new BasicGraphicsComponent(&window, boxes_body[i]->sprites.at(0)),
	new BasicPhysicsComponent(boxes_body[i]->body) }
	);

	EntityManager::RegisterEntity(boxes[i]);

	}
	*/

	Entity * box;
	Item * box_body;
	box_body = Factory::CreateItem<Box>(BOX_2_SF(1), BOX_2_SF(1));
	box_body->body->SetAngularDamping(2);
	box_body->body->SetTransform(b2Vec2(300 / WORLD_SCALE, 300 / WORLD_SCALE), DEGREES_2_RAD(40));

	box = new 	Entity(
	{ new BasicGraphicsComponent(&window, box_body->sprites),
		new BasicPhysicsComponent(box_body->body) }
	);

	EntityManager::RegisterEntity(box);

	







	//------------------------
	// Main Loop
	//------------------------

	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		//window.clear();
		Globals::IncrTimer();
		EventHandler::GetEvents(window);
		EntityManager::Update(window);
		Globals::world.Step(timeStep, velocityIterations, positionIterations);
		EventHandler::ClearEvents();
		window.display();

	}

	return 0;
}
