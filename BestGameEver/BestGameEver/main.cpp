#include <SFML/Graphics.hpp>
#include <string> 

using namespace sf;

#define VEL_MAX		.1
#define FRICTION	0.0005  // must be less than 1... or else you get like negative friction
#define FORCE		0.0001
#define GRAVITY		0.0001
#define JUMP_FORCE	0.25
#define JET_MAX		100000
#define JET_FORCE	0.00025
#define MASS		1.4

int main()
{

	RenderWindow window(VideoMode(800, 600), "FFFFF", Style::Default);

	Font font;
	font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
	sf::Clock deltaClock;
	Text text;
	Text jet_status;
	std::string jetstring;
	text.setFont(font);
	jet_status.setFont(font);
	char mander = '>';
	bool jet_flag = false;

	double x_pos=200.0, y_pos=200.0, x_vel=0, y_vel=0, jetpack = JET_MAX;

	while (window.isOpen())
	{

		sf::Time deltaTime = deltaClock.restart();

		Event evnt;

		
	//	printf("%d", deltaTime.asMilliseconds());

		// This is why we should use a loop for polling. Makes sure the queue doesn't fill up with events
		/// \brief Pop the event on top of the event queue, if any, and return it
		///
		/// This function is not blocking: if there's no pending event then
		/// it will return false and leave \a event unmodified.
		/// Note that more than one event may be present in the event queue,
		/// thus you should always call this function in a loop
		/// to make sure that you process every pending event.
		///
		/// \return True if an event was returned, or false if the event queue was empty
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
		//Player Movement
		//------------------------

		// Adjust Velocity: Accelerate the player
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			x_vel -= FORCE/MASS;	// if key pressed, increase velocity
			x_vel = abs(x_vel) > VEL_MAX ? -1*VEL_MAX : x_vel; // cap velocity at VEL_MAX
			mander = '<'; // change character direction
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			y_vel -= FORCE/MASS;
			y_vel = abs(y_vel) > VEL_MAX ? -1 * VEL_MAX : y_vel;
			mander = '^';
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			x_vel += FORCE/MASS;
			x_vel = abs(x_vel) > VEL_MAX ? VEL_MAX : x_vel;
			mander = '>';
		}

		// Allows player to use jetpack
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && jetpack > 0) {
			y_vel += JET_FORCE/MASS;
			jetpack--;
			mander = 'v';
			jet_flag = true;
		}

		// Allows player to jump
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && y_pos == 0) {
			y_vel += JUMP_FORCE/MASS;
			mander = 'v';
		}


		//------------------------
		//Player Environment
		//------------------------


		// Recharge Jetpack: Only if jet not used and jetpack isn't fully charged
		if (jetpack < JET_MAX && jet_flag == false) {
			jetpack += 2;
		}

		// Adjust Velocity: Deccelerate the player
		x_vel -= x_vel*FRICTION;	// reduce left velocity. FRICTION is < 1
		y_vel -= (y_vel*FRICTION + GRAVITY*MASS); // Apply friction and gravity in Y direction

		// Adjust Position: Change position using velocity
		x_pos += x_vel;
		y_pos += y_vel;

		// Edge Case: Prevent player from floating off screen; Reset jet used flag
		if (y_pos <= 0) {
			y_pos = 0;
			y_vel = 0;
			jet_flag = false;
		}

		//------------------------
		//Windows managment
		//------------------------

		
		// Print character to screen 
		jetstring = std::to_string((int)jetpack);
		text.setPosition(x_pos, y_pos);
		text.setString(mander);
		jet_status.setPosition(10, 500);
		jet_status.setString(jetstring);
		window.clear();
		window.draw(text);
		window.draw(jet_status);
		window.display();

	}

	return 0;
}