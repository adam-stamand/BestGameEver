#include <SFML/Graphics.hpp>
#include <new> 
#include "Box2D/Box2D.h"
#include <string> 

#include "Entity/Entity.h"
#include "Components/Components.h"
#include "Level/EventHandler.h"


int main()
{

	b2Vec2 gravity(0.0f, 0.0f);
	b2World world(gravity);


	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(400.0f, 550.0f);

	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(400.0f, 0.0f);

	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);









	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(110.0f, 305.0f);
	b2Body* body = world.CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	b2Vec2 vec[3];


	vec[0].Set(20, 10);
	vec[1].Set(30,50);
	vec[2].Set(50,10);
	dynamicBox.Set(vec, 3);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 3.0f;

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);

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
		 new BasicGraphicsComponent("Images/rocket_ship.jpg", &window),
		 new RocketPhysicsComponent(body, &world)}, 
		50, 
		50, 
		0
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
