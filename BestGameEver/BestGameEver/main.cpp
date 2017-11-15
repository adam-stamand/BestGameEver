#include <SFML/Graphics.hpp>
#include <new> 
#include "Box2D/Box2D.h"
#include <string> 
#include "SFML/Audio.hpp""
#include "Entity/Entity.h"
#include "Components/Components.h"
#include "Level/EventHandler.h"
#include "Level/EntityManager.h"


void CreateStructure(b2Vec2 coords[], int num_coords) {


}

int main()
{
	b2Vec2 gravity(0.0f, 0.1f);
	b2World world(gravity);


	// Define ground
	b2Vec2 groundBoxCoord[] = { b2Vec2(0,0),b2Vec2(800,0),b2Vec2(800,600),b2Vec2(0,600) };
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

	

	// Define the dynamic body. We set its position and call the body factory.
	std::string str = "Images/rocket_ship.png";
	sf::Texture texture;
	texture.loadFromFile(str);
	sf::Sprite sprite;
	sprite.setTexture(texture);


	float tempx = (float)texture.getSize().x;
	float tempy = (float)texture.getSize().y;
	sprite.setOrigin(tempx/2, tempy/2);
	tempx *= .0125;
	tempy *= .0125;

	sprite.setScale(.0125f, 0.0125f);
	

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(110.0f, 305.0f);
	b2Body* body = world.CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(tempx / 2, tempy / 2);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;
	// Override the default friction.
	fixtureDef.friction = 3.0f;
	fixtureDef.restitution = .15;

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);
	body->SetAngularDamping(.05);

	b2MassData massD;
	body->GetMassData(&massD);
	printf("x:%f, y:%f\n", massD.center.x, tempy / 2);
	massD.center = b2Vec2(0, -15);
	body->SetMassData(&massD);



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
	music.play();

	Entity main_ent(
		{new RocketControlsComponent,
		 new BasicGraphicsComponent(&window, &sprite),
		 new RocketPhysicsComponent(body, &world)}
	);
	
	EntityManager::RegisterEntity(&main_ent);

	
	//Entity box(
	//	{new BasicGraphicsComponent(&window, &sprite),
	//	 new BasicPhysicsComponent(body, &world)}
	//);

	//EntityManager::RegisterEntity(&box);


	//------------------------
	// Main Loop
	//------------------------
	

	while (window.isOpen())
	{


		EventHandler::GetEvents(window);
		EntityManager::Update(window);
		world.Step(timeStep, velocityIterations, positionIterations);
		EventHandler::ClearEvents();

		//sf::Time deltaTime = deltaClock.restart();
		//while (deltaClock.getElapsedTime().asMilliseconds() < 17) {
		//	printf("%d\n", deltaClock.getElapsedTime().asMilliseconds());
	//	}
	//	deltaClock.restart();
	
	}

	return 0;
}
