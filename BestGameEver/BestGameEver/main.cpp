#include <SFML/Graphics.hpp>
#include <new> 
#include "Box2D/Box2D.h"
#include <string> 
#include "SFML/Audio.hpp""
#include "Entity/Entity.h"
#include "Components/Components.h"
#include "Level/EventHandler.h"
#include "Level/EntityManager.h"
#include <stdlib.h>
#include "windows.h" 

sf::Sprite * CreateSprite(std::string str, float setX, float setY) {
	sf::Texture * texture = new sf::Texture;
	texture->loadFromFile(str);
	sf::Sprite * sprite = new sf::Sprite;

	sprite->setTexture(*texture);
	float currX, currY, scaleX, scaleY;
	currX = (float)texture->getSize().x;
	currY = (float)texture->getSize().y;
	
	scaleX = setX / currX;
	scaleY = setY / currY;

	sprite->setScale(scaleX, scaleY);
	sprite->setOrigin(currX / 2, currY / 2);
	return sprite;
}


b2PolygonShape * CreateShape(sf::Sprite &sprite, b2Vec2 vec[], int verts) {
	
	b2PolygonShape * shape = new b2PolygonShape;
	float xSize = sprite.getTexture()->getSize().x;
	float ySize = sprite.getTexture()->getSize().y;

	float xScale = sprite.getScale().x;
	float yScale = sprite.getScale().y;

	for (int i = 0; i < verts; i++) {
		vec[i].x =(vec[i].x * xScale * xSize *1/30) - (xScale *xSize / 2  *1 / 30);
		vec[i].y = (vec[i].y * yScale * ySize *1/30) - (yScale *ySize / 2 *1 / 30);
		printf("sizex:%f, sizey:%f\n", vec[i].x, vec[i].y);
	}

	shape->Set(vec, verts);
	return shape;
}



b2Body * CreateBody(b2BodyType type, b2World &world, b2FixtureDef * fixture, float xPos, float yPos) {
	b2BodyDef * bodyDef = new b2BodyDef;
	bodyDef->type = b2_dynamicBody;
	bodyDef->position.Set(xPos, yPos);
	b2Body * body = world.CreateBody(bodyDef);
	body->CreateFixture(fixture);
	return body;
}

b2FixtureDef * CreateFixture(sf::Sprite &sprite, b2Vec2 vec[], int verts) {
	b2FixtureDef * fixtureDef = new b2FixtureDef;
	fixtureDef->shape = CreateShape(sprite, vec, verts);
	return fixtureDef;
}

b2FixtureDef * CreateFixture(sf::Sprite &sprite) {
	b2FixtureDef * fixtureDef = new b2FixtureDef;
	int verts = 4;
	b2Vec2 vec[4];
	vec[0] = b2Vec2(0, 0);
	vec[1] = b2Vec2(0, 1);
	vec[2] = b2Vec2(1, 1);
	vec[3] = b2Vec2(1, 0);
	fixtureDef->shape = CreateShape(sprite, vec, verts);
	return fixtureDef;
}




int main()
{
	b2Vec2 gravity(0.0f, 10.0f);
	b2World world(gravity);


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

	
	// TODO: Add material definitions to fixtures!!
	
	// Define the dynamic body. We set its position and call the body factory.
	b2MassData massD;
	b2Vec2 vec[] = { b2Vec2(.5,0), b2Vec2(1,0.65), b2Vec2(1,1), b2Vec2(0,1),b2Vec2(0, 0.65) };

	sf::Sprite * sprite = CreateSprite("Images/rocket_ship.png", 1500/30, 2000/30);

	b2FixtureDef * fixtureDef = CreateFixture(*sprite);
	fixtureDef->density = 1.0f;
	fixtureDef->friction = 3.0f;
	fixtureDef->restitution = 0;

	b2Body * body = CreateBody(b2_dynamicBody, world, fixtureDef, 250/30,250/30);
	body->SetAngularDamping(1);
	//body->SetLinearDamping(0);
	//body->GetMassData(&massD);
	//massD.center = b2Vec2(0, -15/25);
	printf("mass:%f\n", massD.mass);
	//body->SetMassData(&massD);

	//
	//
	//


	sf::Sprite * sprite2 = CreateSprite("Images/box.png", 35/30, 35/30);

	b2FixtureDef * fixtureDef2 = CreateFixture(*sprite2);
	fixtureDef2->density = .5f;
	fixtureDef2->friction = 1.0f;
	fixtureDef2->restitution = .5;

	b2Body * body2 = CreateBody(b2_dynamicBody, world, fixtureDef2, 400, 500);
	body2->SetAngularDamping(.05);

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
		 new BasicGraphicsComponent(&window, sprite),
		 new RocketPhysicsComponent(body, &world)},
		50,
		150
	);
	
	EntityManager::RegisterEntity(&main_ent);

	
	Entity box(
		{new BasicGraphicsComponent(&window, sprite2),
		 new BasicPhysicsComponent(body2, &world)},
		500,
		50
	);

	//EntityManager::RegisterEntity(&box);


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
