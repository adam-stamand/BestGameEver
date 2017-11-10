#include <SFML/Graphics.hpp>
#include <string> 

#include "Entity/Entity.h"
#include "Components/MainControlsComponent.h"
#include "Components/MainGraphicsComponent.h"
#include "Components/MainPhysicsComponent.h"
#include <new> 

using namespace sf;


int main()
{

	//------------------------
	// Init
	//------------------------

	RenderWindow window(VideoMode(800, 600), "FFFFF", Style::Default);
	sf::Clock deltaClock;
	
	typedef std::vector<Component *> ComponentVec;
	
	ComponentVec components;
	
	components = { new MainControlsComponent, new MainGraphicsComponent('>'), new MainPhysicsComponent(2, -0.00002, 0.001) };
	Entity main_ent(components, 50, 50);
	components.clear();

	components = { new MainGraphicsComponent('0'), new MainPhysicsComponent(4, 0, 0.001) };
	Entity box(components, 200, 200);
	components.clear();


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
	
	while (window.isOpen())
	{
		window.clear();
		main_ent.Update(window);
		box.Update(window);
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
