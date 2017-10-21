#include <SFML/Graphics.hpp>

using namespace sf;



#define VEL_MAX 1
#define FRICTION 0.0005 // must be less than 1... or else you get like negative friction
#define ACCEL	0.0001
#define GRAVITY 0.00007
#define JUMP	0.15
#define JET_MAX	20000
#define JET_ACCEL 0.00009

int main()
{

	RenderWindow window(VideoMode(800, 600), "FFFFF", Style::Default);

	Font font;
	font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
	sf::Clock deltaClock;
	Text text;
	text.setFont(font);

	char mander = '>';

	double x_pos=200.0, y_pos=200.0, x_vel=0, y_vel=0, jetpack = JET_MAX, jet_intr = 2;

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

		// Manage the velocity of the player

		// Accelerate the player
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			x_vel -= ACCEL;	// if key pressed, increase velocity
			x_vel = abs(x_vel) > VEL_MAX ? -1*VEL_MAX : x_vel; // cap velocity at VEL_MAX
			mander = '<'; // change character direction
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			y_vel -= ACCEL;
			y_vel = abs(y_vel) > VEL_MAX ? -1 * VEL_MAX : y_vel;
			mander = '^';
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			x_vel += ACCEL;
			x_vel = abs(x_vel) > VEL_MAX ? VEL_MAX : x_vel;
			mander = '>';
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && jetpack > 0) {
			y_vel += JET_ACCEL;
			y_vel = abs(y_vel) > VEL_MAX ? VEL_MAX : y_vel;
			jetpack -= jet_intr;
			mander = 'v';
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && y_pos <= 0) {
			y_vel += JUMP;
			y_vel = abs(y_vel) > VEL_MAX ? VEL_MAX : y_vel;
			mander = 'v';
		}

		// Deccelerate the player
		if (x_vel < 0) {	// if player moving to the left
			x_vel -= x_vel*FRICTION;	// reduce left velocity. FRICTION is < 1
		}
		else if (x_vel > 0){
			x_vel -= x_vel*FRICTION;
		}

		if (y_vel < 0) {
			y_vel -= y_vel*FRICTION;
		}
		else if (y_vel > 0) {
			y_vel -= y_vel*FRICTION;
		}
		
		// If above the "ground", apply gravity to velocity
		if (y_pos > 0) {
			y_vel -= GRAVITY;
		}


		if (y_pos <= 0 && jetpack < JET_MAX) {
			jetpack += jet_intr;
		}

		// Change position using velocity
		x_pos += x_vel;
		y_pos += y_vel;


		// Prevent player from floating off screen
		if (y_pos < 0) {
			y_pos = 0;
		}

		// Print character to screen 
		text.setPosition(x_pos, y_pos);
		text.setString(mander);
		window.clear();
		window.draw(text);
		window.display();

	}

	return 0;
}