#include <SFML/Graphics.hpp>
#include <string> 
#include "Controllable.h"
#include "Uncontrollable.h"

using namespace sf;

#define VEL_MAX		.1
#define FORCE		.0001f
#define JUMP_FORCE	0.1f
#define MASS		1.4f


// Put together Entity, Movable/Immovable, and Controllable/Uncontrollable

// I commented out Gravity since we're not doing any boundary detection. It's pretty fun without gravity though

// I put collission stuff inside movable. This implies that immovable entities don't collide with movable, rather
// movable entities collide with immovable. I'm fine with that implication if you are.

// The next big step is implementing Immovable entities. That will allow us to start creating actual boundaries.
// There's a method inside Movable for handling collisions with Immovables, but I just copied pasted, so it needs to be looked at.
// Much like Uncontrollable, I expect Immovable to be pretty much empty.

// Also, I found a bug in the ellastic collision math, so the fix you made may not be necessary, even when we start using gravity again

// Lastly, in the main, I've added two objects, just to see how easy it is to create new entities. The initializing process is a little hefty,
// but we can wrap it up in some init function. Everything I did is either straight forward or the same as it was, with the exception of the 
// Controllable. I wanted to let a user define multiple keys for an action instead of just one (i.e. "shift" and "W" could be run, just "W" could be walk)
// So I started using vectors. This is my first time using them, and the only reason I did is because, unlike arrays, they change size dynamically
// behind the scenes, so we don't have to deal with it. Anyway, good luck.

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

	Controllable player;
	player.SetMass(1.9);
	box.SetXSize(20);
	box.SetYSize(20);

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
		sf::Time deltaTime = deltaClock.restart();
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
		if (player.DetectCollision(box, box2)) {
			player.ObjectCollision(box, box2);
		}

		
		/*
		// If either object gets close to border, call boundary collision
		if (((box_mover.GetXPos() <= 0) && (box_mover.GetXVel() < 0)) || ((box_mover.GetXPos() >= 780) && (box_mover.GetXVel() > 0)) ) {
			BoundaryXCollision(box_mover);
		}
		if (((box_mover.GetYPos() <= 0) && (box_mover.GetYVel() < 0)) || (box_mover.GetYPos() >= 580)) {
			BoundaryYCollision(box_mover);
		}
		if (((mover.GetXPos() <= 0) && (mover.GetXVel() < 0)) || ((mover.GetXPos() >= 780) && (mover.GetXVel() > 0)) ) {
			BoundaryXCollision(mover);
		}
		if (((mover.GetYPos() <= 0) && (mover.GetYVel() < 0)) || (mover.GetYPos() >= 580)) {
			BoundaryYCollision(mover);
		}

		// Check that objects are within bounds
		CheckBoundary(mover);
		CheckBoundary(box_mover);
		*/


		// Recharge Jetpack: Only if jet not used and jetpack isn't fully charged
		//if (jetpack < JET_MAX && jet_flag == false) {
		//	jetpack += 2;
		//}



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
