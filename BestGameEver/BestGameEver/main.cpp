#include <SFML/Graphics.hpp>
#include <new> 
#include "Box2D/Box2D.h"
#include <string> 
#include "SFML/Audio.hpp"
#include "Globals/Globals.h"
#include "Factory/Factory.h"
#include "Entity/Entity.h"
#include "Components/Components.h"
#include "Level/EventHandler.h"
#include "Level/EntityManager.h"
#include <stdlib.h>



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

	if (!music.openFromFile("Music/BestGameEverMaster.wav")) {
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
	groundBody = world.CreateBody(&groundBodyDef);
	groundBody->CreateFixture(&groundFixtureDef);


	b2CircleShape circleShape;
	circleShape.m_p.Set(0, 0); //position, relative to body position
	circleShape.m_radius = 1; //radius
	

	
	Item * rocket = Factory::CreateItem<Rocket>(BOX_2_SF(1), BOX_2_SF(2));
	rocket->body->SetAngularDamping(3);
	rocket->body->SetLinearDamping(0);
	rocket->body->SetTransform(b2Vec2(200 / WORLD_SCALE, 200 / WORLD_SCALE), 0);


	sf::Sprite * tree = Factory::CreateSprite(IMAGE(tree.png), BOX_2_SF(2), BOX_2_SF(4));
	sf::Sprite * background = Factory::CreateSprite(IMAGE(sky_background.png), 800, 600);


	//------------------------
	// Create Entities
	//------------------------

	Entity background_ent(
		{ new BasicGraphicsComponent(&window, background) },
		400.0, 300.0
	);

	EntityManager::RegisterEntity(&background_ent);



	Entity * trees[5];
	for (int i = 0; i < 5; i++) {
		trees[i] = new Entity(
			{ new BasicGraphicsComponent(&window, tree) },
			i*150+100, 525.0
		);
		EntityManager::RegisterEntity(trees[i]);
	}



	Entity main_ent(
		{new RocketControlsComponent,
		 new BasicGraphicsComponent(&window, rocket->sprites.at(0)),
		 new RocketPhysicsComponent(rocket->body)}
	);
	
	EntityManager::RegisterEntity(&main_ent);

	Entity * boxes[6];
	Item * boxes_body[6];
	for (int i = 0; i < 6; i++) {
		boxes_body[i] = Factory::CreateItem<Box>(BOX_2_SF(1), BOX_2_SF(1));
		boxes_body[i]->body->SetAngularDamping(2);
		boxes_body[i]->body->SetTransform(b2Vec2(300 / WORLD_SCALE, 300 / WORLD_SCALE), DEGREES_2_RAD(40));

		boxes[i] = new 	Entity(
		{ new BasicGraphicsComponent(&window, boxes_body[i]->sprites.at(0)),
		new BasicPhysicsComponent(boxes_body[i]->body) },
			i * 100 + 20, 400
		);

		EntityManager::RegisterEntity(boxes[i]);

	}





	//------------------------
	// Main Loop
	//------------------------

	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		//window.clear();
		EventHandler::GetEvents(window);
		EntityManager::Update(window);
		world.Step(timeStep, velocityIterations, positionIterations);
		EventHandler::ClearEvents();
		window.display();

	}

	return 0;
}
