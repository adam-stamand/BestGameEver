#include <SFML/Graphics.hpp>
#include <string> 
#include "Uncontrollable.h"
#include "LinkedList.h"
#include "Node.h"
#include "EventHandler.h"
#include "ImmovableTable.h"
#include "screen_temp.h"

using namespace sf;

#define VEL_MAX		.1 

#define JUMP_FORCE	0.1f
#define MASS		1.4f



int main()
{
	RenderWindow window(VideoMode(800, 600), "FFFFF", Style::Default);


	sf::Clock deltaClock;

	//------------------------
	// Init
	//------------------------

	sf::Font font;
	font.loadFromFile("C:/Windows/Fonts/Arial.ttf");


	LinkedList<Immovable> ll;
	Immovable j(50, 50, 5, 5);
	Immovable i(60, 60, 6, 6);

	ImmovableTable it(50);
	it.add(i);
	it.add(j);



	Movable player;
	player.SetMass(1.9);
	player.SetXSize(20);
	player.SetYSize(20);
	player.SetXPos(60);
	player.SetYPos(60);


	Uncontrollable box;
	box.SetMass(1);
	box.SetXPos(200);
	box.SetYPos(200);
	box.SetXVel(0);
	box.SetYVel(0);
	box.SetXSize(20);
	box.SetYSize(20);

	Uncontrollable box2;
	box2.SetMass(2);
	box2.SetXPos(400);
	box2.SetYPos(200);
	box2.SetXVel(0);
	box2.SetYVel(0);
	box2.SetXSize(20);
	box2.SetYSize(20);


	sf::Text player_text;
	player_text.setString(">");
	player_text.setCharacterSize(50);
	player_text.setPosition(40, 40);
	player_text.setFont(font);

	sf::Text box2_text;
	box2_text.setString("0");
	box2_text.setCharacterSize(20);
	box2_text.setPosition(140, 140);
	box2_text.setFont(font);

	sf::Text box1_text;
	box1_text.setString("O");
	box1_text.setCharacterSize(30);
	box1_text.setPosition(240, 240);
	box1_text.setFont(font);

	screen_temp::text_objects.push_back(player_text);
	screen_temp::text_objects.push_back(box1_text);
	screen_temp::text_objects.push_back(box2_text);

	screen_temp::level_objects.push_back(player);
	screen_temp::level_objects.push_back(box);
	screen_temp::level_objects.push_back(box2);




	Immovable ceiling(400, -20, 800, 20);
	Immovable floor(400, 560, 800, 20);
	Immovable leftWall(-20, 300, 20, 600);
	Immovable rightWall(780, 300, 20, 600);



	std::vector<sf::Keyboard::Key> key_vec;
	Movable::KeyPressAction key_event;
	
	key_vec.push_back(sf::Keyboard::W);
	key_event.func_ptr = &Movable::MoveUp;
	key_event.ID = 1;
	key_event.keys_pressed = key_vec;
	screen_temp::level_objects.at(0).RegisterKeyPressAction(key_event);
	key_vec.clear();
	key_event.keys_pressed.clear();
	
	key_vec.push_back(sf::Keyboard::S);
	key_event.func_ptr = &Movable::MoveDown;
	key_event.ID = 2;
	key_event.keys_pressed = key_vec;
	screen_temp::level_objects.at(0).RegisterKeyPressAction(key_event);
	key_vec.clear();
	key_event.keys_pressed.clear();
	
	key_vec.push_back(sf::Keyboard::D); 
	key_event.func_ptr = &Movable::MoveRight;
	key_event.ID = 3;
	key_event.keys_pressed = key_vec;
	screen_temp::level_objects.at(0).RegisterKeyPressAction(key_event);
	key_vec.clear();
	key_event.keys_pressed.clear();

	key_vec.push_back(sf::Keyboard::A); 
	key_event.func_ptr = &Movable::MoveLeft;
	key_event.ID = 4;
	key_event.keys_pressed = key_vec;
	screen_temp::level_objects.at(0).RegisterKeyPressAction(key_event);
	key_vec.clear();
	key_event.keys_pressed.clear();
	
	screen_temp screen;
	screen_temp::EventAction evnt_action;
	evnt_action.func_ptr = &screen_temp::SpawnBox;
	key_event.ID = 6;
	evnt_action.evnt_type = sf::Event::MouseButtonPressed;
	screen.RegisterEventAction(evnt_action);


	//------------------------
	// Main Loop
	//------------------------

	while (window.isOpen())
	{
		//sf::Time deltaTime = deltaClock.restart();
		//while (deltaClock.getElapsedTime().asMilliseconds() < 17) {
		//	printf("%d\n", deltaClock.getElapsedTime().asMilliseconds());
	//	}
	//	deltaClock.restart();
	//	printf("%d", deltaTime.asMilliseconds());

	//	printf("%d", deltaTime.asMilliseconds());
	//	printf("%d", (int) ll.getNode(1)->element.GetXSize());
	
		//------------------------
		// Player Environment
		//------------------------

		
		// If two objects are close, call a collision
		for (int i = 0; i <screen_temp::level_objects.size(); i++) {
			if (screen_temp::level_objects.at(i).DetectCollision(screen_temp::level_objects.at(i), ceiling)) {
				screen_temp::level_objects.at(i).ObjectCollision(screen_temp::level_objects.at(i), ceiling);
			}
			if (screen_temp::level_objects.at(i).DetectCollision(screen_temp::level_objects.at(i), rightWall)) {
				screen_temp::level_objects.at(i).ObjectCollision(screen_temp::level_objects.at(i), rightWall);
			}

			if (screen_temp::level_objects.at(i).DetectCollision(screen_temp::level_objects.at(i), leftWall)) {
				screen_temp::level_objects.at(i).ObjectCollision(screen_temp::level_objects.at(i), leftWall);
			}

			if (screen_temp::level_objects.at(i).DetectCollision(screen_temp::level_objects.at(i), floor)) {
				screen_temp::level_objects.at(i).ObjectCollision(screen_temp::level_objects.at(i), floor);
			}
			for (int j = i+1; j < screen_temp::level_objects.size(); j++) {
				if (screen_temp::level_objects.at(i).DetectCollision(screen_temp::level_objects.at(i), screen_temp::level_objects.at(j))) {
					screen_temp::level_objects.at(i).ObjectCollision(screen_temp::level_objects.at(i), screen_temp::level_objects.at(j));
				}
			}

		}

		/*

		if (level_objects.at(0).DetectCollision(level_objects.at(0), box)) {
			level_objects.at(0).ObjectCollision(level_objects.at(0), box);
		}
		if (level_objects.at(0).DetectCollision(level_objects.at(0), box2)) {
			level_objects.at(0).ObjectCollision(level_objects.at(0), box2);
		}

		if (level_objects.at(0).DetectCollision(level_objects.at(0), ceiling)) {
			level_objects.at(0).ObjectCollision(level_objects.at(0), ceiling);
		}
		if (level_objects.at(0).DetectCollision(level_objects.at(0), leftWall)) {
			level_objects.at(0).ObjectCollision(level_objects.at(0), leftWall);
		}
		if (level_objects.at(0).DetectCollision(level_objects.at(0), floor)) {
			level_objects.at(0).ObjectCollision(level_objects.at(0), floor);
		}
		if (level_objects.at(0).DetectCollision(level_objects.at(0), rightWall)) {
			level_objects.at(0).ObjectCollision(level_objects.at(0), rightWall);
		}

		if (level_objects.at(0).DetectCollision(level_objects.at(1), level_objects.at(2))) {
			level_objects.at(0).ObjectCollision(box, level_objects.at(2));
		}

		if (level_objects.at(0).DetectCollision(box, ceiling)) {
			level_objects.at(0).ObjectCollision(box, ceiling);
		}

		if (level_objects.at(0).DetectCollision(box, floor)) {
			level_objects.at(0).ObjectCollision(box, floor);
		}

		if (level_objects.at(0).DetectCollision(box, leftWall)) {
			level_objects.at(0).ObjectCollision(box, leftWall);
		}

		if (level_objects.at(0).DetectCollision(box, rightWall)) {
			level_objects.at(0).ObjectCollision(box, rightWall);
		}

		if (level_objects.at(0).DetectCollision(box2, ceiling)) {
			level_objects.at(0).ObjectCollision(box2, ceiling);
		}

		if (level_objects.at(0).DetectCollision(box2, floor)) {
			level_objects.at(0).ObjectCollision(box2, floor);
		}

		if (level_objects.at(0).DetectCollision(box2, leftWall)) {
			level_objects.at(0).ObjectCollision(box2, leftWall);
		}

		if (level_objects.at(0).DetectCollision(box2, rightWall)) {
			level_objects.at(0).ObjectCollision(box2, rightWall);
		}

		*/

		// Update Positions and check controls

		EventHandler::GetEvents(window);

		screen.CheckEventActions(screen);
		screen_temp::level_objects.at(0).CheckKeyPressActions(screen_temp::level_objects.at(0));

		EventHandler::ClearEvents();

		for (int i = 0; i < screen_temp::text_objects.size(); i++) {
			screen_temp::level_objects.at(i).UpdatePosition();
		}



		//------------------------
		// Windows managment
		//------------------------
		
		window.clear();
		for (int i = 0; i < screen_temp::text_objects.size(); i++) {
			screen_temp::text_objects.at(i).setFont(font);
			(screen_temp::text_objects.at(i)).setPosition((screen_temp::level_objects.at(i)).GetXPos(), (screen_temp::level_objects.at(i)).GetYPos());
			window.draw(screen_temp::text_objects.at(i));
		}
		


		window.display();



	}

	return 0;
}
