#include <SFML/Graphics.hpp>
#include <new> 
#include "Box2D/Box2D.h"
#include <string> 
#include "SFML/Audio.hpp""
#include "World/World.h"
#include "Factory/Factory.h"
#include "Entity/Entity.h"
#include "Components/Components.h"
#include "Level/EventHandler.h"
#include "Level/EntityManager.h"
#include <stdlib.h>



int main()
{

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
	groundBody = world.CreateBody(&groundBodyDef);
	groundBody->CreateFixture(&groundFixtureDef);

	
	Item * rocket = Factory::CreateItem<Rocket>(30, 70);
	rocket->body->SetAngularDamping(2);
	rocket->body->SetLinearDamping(0);

	Item * box = Factory::CreateItem<Box>(30, 30);
	rocket->body->SetAngularDamping(2);


	sf::Sprite * tree = Factory::CreateSprite("Images/tree.png", 70, 150);


	//------------------------
	// Init
	//------------------------

	sf::RenderWindow window(sf::VideoMode(800, 600), "FFFFF", sf::Style::Default);
	sf::Clock deltaClock;
	sf::Music music;
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;



	if (!music.openFromFile("Music/BestGameEverMaster.wav")) {
		return -1;
	}
	music.setLoop(true);
	//music.play();

	Entity main_ent(
		{new RocketControlsComponent,
		 new BasicGraphicsComponent(&window, rocket->sprites.at(0)),
		 new RocketPhysicsComponent(rocket->body, &world)}
	);
	
	EntityManager::RegisterEntity(&main_ent);

	
	Entity box_ent(
		{new BasicGraphicsComponent(&window, box->sprites.at(0)),
		 new BasicPhysicsComponent(box->body, &world)}
	);

	EntityManager::RegisterEntity(&box_ent);


	Entity tree_ent(
		{new BasicGraphicsComponent(&window, tree)}
	);

	EntityManager::RegisterEntity(&tree_ent);

	//------------------------
	// Main Loop
	//------------------------

	window.setFramerateLimit(60);

	while (window.isOpen())
	{

		EventHandler::GetEvents(window);
		EntityManager::Update(window);
		world.Step(timeStep, velocityIterations, positionIterations);
		EventHandler::ClearEvents();

	}

	return 0;
}
