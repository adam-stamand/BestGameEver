#include <SFML/Graphics.hpp>
#include <new> 
#include "Box2D/Box2D.h"
#include <string> 
#include "SFML/Audio.hpp""
#include "Entity/Entity.h"
#include "Components/Components.h"
#include "Level/EventHandler.h"


int main()
{
	b2Vec2 gravity(0.0f, 0.1f);
	b2World world(gravity);

	b2Vec2 groundBoxCoord[] = { b2Vec2(0,0),b2Vec2(800,0),b2Vec2(800,600),b2Vec2(0,600) };

	b2ChainShape groundChain;
	b2BodyDef groundBodyDef;
	b2FixtureDef groundFixtureDef;
	sf::Music music;
	if (!music.openFromFile("Music/BestGameEverMaster.wav")) {
		return -1;
	}
	music.setLoop(true);
	music.play();


	groundChain.CreateLoop(groundBoxCoord, 4);

	groundBodyDef.type = b2_staticBody;
	groundBodyDef.position.Set(0, 0);
	groundFixtureDef.shape = &groundChain;
	b2Body* groundBody = world.CreateBody(&groundBodyDef);
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
	//this->sprite.setColor(sf::Color(0, 55, 05, 128));
	//this->sprite.setPosition(200.f, 100.f);
	//this->sprite.setRotation(30.f);
	//sf::FloatRect rect = sprite.getGlobalBounds();

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
	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;


	//------------------------
	// Init
	//------------------------

	sf::RenderWindow window(sf::VideoMode(800, 600), "FFFFF", sf::Style::Default);
	sf::Clock deltaClock;
	

	Entity main_ent(
		{new RocketControlsComponent,
		 new BasicGraphicsComponent(&window, &sprite),
		 new RocketPhysicsComponent(body, &world)}
	);
	
	//components = { new MainGraphicsComponent('0'), new MainPhysicsComponent(4, 0, 0.001) };
	//Entity box(components, 200, 200);
	//components.clear();


	/*


	MainCharacter::EventAction evnt_action;
	evnt_action.func_ptr = &MainCharacter::SpawnBox;
	key_event.ID = 6;
	evnt_action.evnt_type = sf::Event::MouseButtonPressed;
	player.RegisterEventAction(evnt_action);

	*/
	//------------------------
	// Main Loop
	//------------------------
	

	while (window.isOpen())
	{


		EventHandler::GetEvents(window);
		window.clear();
		world.Step(timeStep, velocityIterations, positionIterations);
		
		main_ent.Update();
		//box.Update(window);
		EventHandler::ClearEvents();
		window.display();


		//sf::Time deltaTime = deltaClock.restart();
		//while (deltaClock.getElapsedTime().asMilliseconds() < 17) {
		//	printf("%d\n", deltaClock.getElapsedTime().asMilliseconds());
	//	}
	//	deltaClock.restart();
	//	printf("%d", deltaTime.asMilliseconds());

	//	printf("%d", deltaTime.asMilliseconds());
	//	printf("%d", (int) ll.getNode(1)->element.GetXSize());
	
	
	}

	return 0;
}
