#include <SFML/Graphics.hpp>
#include <string> 
#include "Controllable.h"
#include "Uncontrollable.h"

using namespace sf;

#define VEL_MAX		.1 
#define FORCE		.0003f
#define JUMP_FORCE	0.1f
#define MASS		1.4f


int main()
{
	RenderWindow window(VideoMode(800, 600), "FFFFF", Style::Default);

	Font font;
	font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
	sf::Clock deltaClock;
	Text box_text, box2_text, text;

	//------------------------
	// Init
	//------------------------

	box_text.setFont(font);
	box2_text.setFont(font);
	text.setFont(font);
	char mander = '>';
	char box_char = '0';
	char box2_char = 'O';


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

	Immovable ceiling(400, -20, 800, 20);
	Immovable floor(400, 560, 800, 20);
	Immovable leftWall(-20, 300, 20, 600);
	Immovable rightWall(780, 300, 20, 600);

	Controllable player;
	player.SetMass(1.9);
	player.SetXSize(20);
	player.SetYSize(20);
	player.SetXPos(60);
	player.SetYPos(60);

	std::vector <Movable::Direction>player_dirs = {
		Movable::Direction::LEFT,
		Movable::Direction::RIGHT,
		Movable::Direction::UP,
		Movable::Direction::DOWN
	};

	std::vector<std::vector<sf::Keyboard::Key>>player_keys = { 
		{sf::Keyboard::A},
		{sf::Keyboard::D},
		{sf::Keyboard::S},
		{ sf::Keyboard::W }
	};

	std::vector<float>player_forces = {
		{ FORCE },
		{ FORCE },
		{ FORCE },
		{ FORCE }
	};

	
	//Initialize player controls
	for (int i = 0; i < player_keys.size(); i++) {
		player.RegisterControl(player_keys.at(i), player_dirs.at(i), player_forces.at(i));
	}
	player_keys.clear();
	
	

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
		Event evnt;

	//	printf("%d", deltaTime.asMilliseconds());

		while (window.pollEvent(evnt))
		{

			switch (evnt.type) 
			{
			case Event::KeyPressed:

				if (evnt.key.code == sf::Keyboard::Escape) {
					window.close();
				}
			}
		}


		//------------------------
		// Player Environment
		//------------------------

		
		// If two objects are close, call a collision
		if (player.DetectCollision(player, box)) {
			player.ObjectCollision(player, box);
		}
		if (player.DetectCollision(player, box2)) {
			player.ObjectCollision(player, box2);
		}

		if (player.DetectCollision(player, ceiling)) {
			player.ObjectCollision(player, ceiling);
		}
		if (player.DetectCollision(player, leftWall)) {
			player.ObjectCollision(player, leftWall);
		}
		if (player.DetectCollision(player, floor)) {
			player.ObjectCollision(player, floor);
		}
		if (player.DetectCollision(player, rightWall)) {
			player.ObjectCollision(player, rightWall);
		}

		if (player.DetectCollision(box, box2)) {
			player.ObjectCollision(box, box2);
		}

		if (player.DetectCollision(box, ceiling)) {
			player.ObjectCollision(box, ceiling);
		}

		if (player.DetectCollision(box, floor)) {
			player.ObjectCollision(box, floor);
		}

		if (player.DetectCollision(box, leftWall)) {
			player.ObjectCollision(box, leftWall);
		}

		if (player.DetectCollision(box, rightWall)) {
			player.ObjectCollision(box, rightWall);
		}

		if (player.DetectCollision(box2, ceiling)) {
			player.ObjectCollision(box2, ceiling);
		}

		if (player.DetectCollision(box2, floor)) {
			player.ObjectCollision(box2, floor);
		}

		if (player.DetectCollision(box2, leftWall)) {
			player.ObjectCollision(box2, leftWall);
		}

		if (player.DetectCollision(box2, rightWall)) {
			player.ObjectCollision(box2, rightWall);
		}


		// Update Positions and check controls

		player.CheckControl();
		player.UpdatePosition();

		box.UpdatePosition();
		box2.UpdatePosition();




		//------------------------
		// Windows managment
		//------------------------

		window.clear();


		text.setString(mander);
		text.setPosition(player.GetXPos(), player.GetYPos());
		window.draw(text);

		box_text.setString(box_char);
		box_text.setPosition(box.GetXPos(), box.GetYPos());
		window.draw(box_text);

		box2_text.setString(box2_char);
		box2_text.setPosition(box2.GetXPos(), box2.GetYPos());
		window.draw(box2_text);


		window.display();



	}

	return 0;
}
