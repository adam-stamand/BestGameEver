#include <SFML/Graphics.hpp>
#include <string> 

#include "Entity/Entity.h"
#include "Components/MainControlsComponent.h"
#include "Components/MainGraphicsComponent.h"
#include "Components/MainPhysicsComponent.h"
#include <new> 
#include "Box2D/Box2D.h"

using namespace sf;


int main()
{

	b2Vec2 gravity(0.0f, .02f);
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
	fixtureDef.friction = 0.3f;

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

	RenderWindow window(VideoMode(800, 600), "FFFFF", Style::Default);
	/*
	sf::Clock deltaClock;
	
	typedef std::vector<Component *> ComponentVec;
	
	ComponentVec components;
	
	components = { new MainControlsComponent, new MainGraphicsComponent('>'), new MainPhysicsComponent(2, -0.00002, 0.001) };
	Entity main_ent(components, 50, 50);
	components.clear();

	components = { new MainGraphicsComponent('0'), new MainPhysicsComponent(4, 0, 0.001) };
	Entity box(components, 200, 200);
	components.clear();

	*/
	/*
	LinkedList<Immovable> ll;
	Immovable j(50, 50, 5, 5);
	Immovable i(60, 60, 6, 6);

	ImmovableTable it(50);
	it.add(i);
	it.add(j);
	
	
	MainCharacter player;
	player.SetText('>');
	player.SetMass(1.9);
	player.SetXSize(20);
	player.SetYSize(20);
	player.SetXPos(60);
	player.SetYPos(60);

	std::vector<sf::Keyboard::Key> key_vec;
	MainCharacter::KeyPressAction key_event;

	key_vec.push_back(sf::Keyboard::W);
	key_event.func_ptr = &MainCharacter::MoveUp;
	key_event.ID = 1;
	key_event.keys_pressed = key_vec;
	player.RegisterKeyPressAction(key_event);
	key_vec.clear();
	key_event.keys_pressed.clear();

	key_vec.push_back(sf::Keyboard::S);
	key_event.func_ptr = &MainCharacter::MoveDown;
	key_event.ID = 2;
	key_event.keys_pressed = key_vec;
	player.RegisterKeyPressAction(key_event);
	key_vec.clear();
	key_event.keys_pressed.clear();

	key_vec.push_back(sf::Keyboard::D);
	key_event.func_ptr = &MainCharacter::MoveRight;
	key_event.ID = 3;
	key_event.keys_pressed = key_vec;
	player.RegisterKeyPressAction(key_event);
	key_vec.clear();
	key_event.keys_pressed.clear();

	key_vec.push_back(sf::Keyboard::A);
	key_event.func_ptr = &MainCharacter::MoveLeft;
	key_event.ID = 4;
	key_event.keys_pressed = key_vec;
	player.RegisterKeyPressAction(key_event);
	key_vec.clear();
	key_event.keys_pressed.clear();



	Item box1;
	box1.SetText('O');
	box1.SetMass(1);
	box1.SetXPos(200);
	box1.SetYPos(200);
	box1.SetXVel(0);
	box1.SetYVel(0);
	box1.SetXSize(20);
	box1.SetYSize(20);

	Item box2;
	box2.SetText('0');
	box2.SetMass(2);
	box2.SetXPos(400);
	box2.SetYPos(200);
	box2.SetXVel(0);
	box2.SetYVel(0);
	box2.SetXSize(20);
	box2.SetYSize(20);

	Structure ceiling(400, -20, 800, 20);
	Structure floor(400, 560, 800, 20);
	Structure leftWall(-20, 300, 20, 600);
	Structure rightWall(780, 300, 20, 600);
	Structure middleWall(400, 300, 20, 300);
	
	Immovable ceiling(400, -20, 800, 20);
	Immovable floor(400, 560, 800, 20);
	Immovable leftWall(-20, 300, 20, 600);
	Immovable rightWall(780, 300, 20, 600);
	



	
	LevelManager::RegisterPlayer(&player);
	LevelManager::RegisterItem(box1);
	LevelManager::RegisterItem(box2);
	LevelManager::RegisterStructure(&ceiling);
	LevelManager::RegisterStructure(&floor);
	LevelManager::RegisterStructure(&leftWall);
	LevelManager::RegisterStructure(&rightWall);
	LevelManager::RegisterStructure(&middleWall);





	MainCharacter::EventAction evnt_action;
	evnt_action.func_ptr = &MainCharacter::SpawnBox;
	key_event.ID = 6;
	evnt_action.evnt_type = sf::Event::MouseButtonPressed;
	player.RegisterEventAction(evnt_action);

	*/
	//------------------------
	// Main Loop
	//------------------------
	
sf:Text text;
sf::Font font;
	text.setString('>');
	text.setCharacterSize(50);
	text.setPosition(40, 40);
	font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
	text.setFont(font);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window : exit
			//if (event.type == sf::Event::Closed)
			//	window.close();
		}
		window.clear();
		world.Step(timeStep, velocityIterations, positionIterations);
		b2Vec2 position = body->GetPosition();
		float32 angle = body->GetAngle();
		text.setPosition(position.x, position.y);
		text.setRotation(angle*30);
		//printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
		//main_ent.Update(window);
		//box.Update(window);
		window.draw(text);
		window.display();


		//sf::Time deltaTime = deltaClock.restart();
		//while (deltaClock.getElapsedTime().asMilliseconds() < 17) {
		//	printf("%d\n", deltaClock.getElapsedTime().asMilliseconds());
	//	}
	//	deltaClock.restart();
	//	printf("%d", deltaTime.asMilliseconds());

	//	printf("%d", deltaTime.asMilliseconds());
	//	printf("%d", (int) ll.getNode(1)->element.GetXSize());
	
	
		//------------------------
		// Check for Collisions
		//------------------------
		//LevelManager::CheckCollisions();

		//------------------------
		// Check for Input
		//------------------------
		//LevelManager::CheckInput(window);
	
		//------------------------
		// Update Position
		//------------------------
		//LevelManager::UpdatePositions();
		
		//------------------------
		// Update Screen
		//------------------------
		//LevelManager::UpdateScreen(window);

	}

	return 0;
}
