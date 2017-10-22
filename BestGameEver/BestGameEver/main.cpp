#include <SFML/Graphics.hpp>
#include <string> 

using namespace sf;

#define VEL_MAX		.1
#define FRICTION	0.0005  // must be less than 1... or else you get like negative friction
#define FORCE		0.0001
#define GRAVITY		0.00009
#define JUMP_FORCE	0.1
#define JET_MAX		5000
#define JET_FORCE	0.00025
#define MASS		1.4


//This morning I had a thought that maybe it would be better to have a class above Movement, like Entity. 
//the reason being is that I'd like to have stationary objects that you can jump on. so Entity would have getxpos, xpos, etc. but wouldn't have velocity or mass, since it would never move.
//I also think that for the sake of the game, jetpack duration should be nerfed quite substantially so the player has to rely on jumping on stationary (and non stationary, like moving platforms or enemies) objects



class Movement { public:
	Movement(float mass, float max_vel);
	~Movement();

	enum Direction {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	void Push(Direction dir, float force);
	void UpdatePosition();
	bool CanJump(Movement &object);
	float GetXPos();
	float GetYPos();
	float GetXVel();
	float GetYVel();
	void SetXPos(float x);
	void SetYPos(float y);
	void SetXVel(float x);
	void SetYVel(float y);
	float mass;
	float max_vel;
	int Xsize; //delete; just temporary
	int Ysize; //delete

private:
	void ApplyFriction();
	void ApplyGravity();

	float y_vel;
	float x_vel;
	float x_pos;
	float y_pos;
};


Movement::Movement(float mass, float max_vel) {
	this->mass = mass;
	this->max_vel = max_vel;
}

Movement::~Movement() {
}

void Movement::SetXPos(float x) {
	this->x_pos = x;
}


void Movement::SetYPos(float y) {
	this->y_pos = y;
}


float Movement::GetXPos() {
	return this->x_pos;
}

float Movement::GetYPos() {
	return this->y_pos;
}

void Movement::SetYVel(float y) {
	this->y_vel = y;
}

void Movement::SetXVel(float x) {
	this->x_vel = x;
}

float Movement::GetXVel() {
	return this->x_vel;
}


float Movement::GetYVel() {
	return this->y_vel;
}

void Movement::Push(Direction dir, float force) {

	switch (dir) {
	case UP:
		this->y_vel += force / this->mass;
		break;

	case DOWN:
		this->y_vel -= force / this->mass;
		break;

	case LEFT:
		this->x_vel -= force / this->mass;
		break;

	case RIGHT:
		this->x_vel += force / this->mass;
		break;
	}
}

void Movement::ApplyFriction() {
	this->y_vel -= this->y_vel * FRICTION;
	this->x_vel -= this->x_vel * FRICTION;
}


void Movement::ApplyGravity() {
	this->y_vel -= GRAVITY;
}

void Movement::UpdatePosition() {
	this->ApplyGravity();
	this->ApplyFriction();
	this->x_pos += this->x_vel;
	this->y_pos += this->y_vel;
}
//need to add a jump cooldown when deltaTime is implemented. atm a jump will have the force of many.
bool Movement::CanJump(Movement &object) { //object needs to be a list of objects
	if (this->GetYPos() < 1) return true;
	if (this->GetYPos() - object.GetYPos() < 20 && abs(this->GetXPos() - object.GetXPos()) < 20) return true;//super temporary. this will eventually work with a list (or tree) of objects and hopefully use variables based on objects size rather than "20"
	return false;
}

// Ellastic Collision
template <typename T1, typename T2>
void ObjectCollision(T1 &object1, T2 &object2) {

	int deltax = object1.GetXPos() - object2.GetXPos();
	int deltay = object1.GetYPos() - object2.GetYPos();

	if (abs(deltax) > abs(deltay)) {
		object2.SetXPos(object2.GetXPos() - ((deltax > 0) - (deltax < 0)) * (object2.Xsize - abs(deltax) + 1) );
	}
	else {
		object2.SetYPos(object2.GetYPos() - ((deltay > 0) - (deltay < 0)) * (object2.Ysize - abs(deltay) + 1) );
	}

	object1.SetXVel(
		(((object1.mass - object2.mass) / (object1.mass + object2.mass)) * object1.GetXVel()) +
		(((2 * object2.mass) / (object1.mass + object2.mass)) * object2.GetXVel())
	);

	object1.SetYVel(
		(((object1.mass - object2.mass) / (object1.mass + object2.mass)) * object1.GetYVel()) +
		(((2 * object2.mass) / (object1.mass + object2.mass)) * object2.GetYVel())
	);


	object2.SetXVel(
		(((object2.mass - object1.mass) / (object1.mass + object2.mass)) * object2.GetXVel()) +
		(((2 * object1.mass) / (object1.mass + object2.mass)) * object1.GetXVel())
	);

	if (object1.GetYPos() <= object2.GetYPos()) { //i had to add this conditional. without it, the object would follow the player when he jumped
		object2.SetYVel(
			(((object2.mass - object1.mass) / (object1.mass + object2.mass)) * object2.GetYVel()) +
			(((2 * object1.mass) / (object1.mass + object2.mass)) * object1.GetYVel())
		);
	}
	
}


// Inelastic Collision (20% Velocity loss)
template <typename T1>
void BoundaryXCollision(T1 &object) {
	object.SetXVel(-object.GetXVel() * 0.8);
	if (object.GetXPos() < 0) {
		object.SetXPos(0);
	}
	else if (object.GetXPos() > 780) {
		object.SetXPos(780);
	}
}

template <typename T1>
void BoundaryYCollision(T1 &object) {
	object.SetYVel(-object.GetYVel() * 0.8);
	if (object.GetYPos() < 0) {
		object.SetYPos(0);
	}
	else if (object.GetYPos() > 580) {
		object.SetYPos(580);
	}
}

template <typename T1>
void CheckBoundary(T1 &object) {
	if (object.GetYPos() < 0) {
		object.SetYPos(0);
	}
	else if (object.GetYPos() > 580) {
		object.SetYPos(580);
	}
	if (object.GetXPos() < 0) {
		object.SetXPos(0);
	}
	else if (object.GetXPos() > 780) {
		object.SetXPos(780);
	}
}


int main()
{

	RenderWindow window(VideoMode(800, 600), "FFFFF", Style::Default);

	Font font;
	font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
	sf::Clock deltaClock;
	Text text;
	Text box_text;
	Text jet_status;
	std::string jetstring;
	box_text.setFont(font);
	text.setFont(font);
	jet_status.setFont(font);
	char mander = '>';
	char box = 'O';
	bool jet_flag = false;

	float jetpack = JET_MAX;
	Movement box_mover(.25, 10);
	box_mover.SetYPos(0);
	box_mover.SetXPos(200);
	box_mover.Xsize = 20;
	box_mover.Ysize = 20;
	Movement mover(MASS, VEL_MAX);
	mover.SetYPos(0);
	mover.SetXPos(0);

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
		//Player Movement
		//------------------------

		// Adjust Velocity: Accelerate the player
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			mover.Push(Movement::Direction::LEFT, FORCE);
			mander = '<'; // change character direction
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			mover.Push(Movement::Direction::DOWN, FORCE);
			mander = '^';
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			mover.Push(Movement::Direction::RIGHT, FORCE);
			mander = '>';
		}

		// Allows player to use jetpack
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && jetpack > 0) {
			mover.Push(Movement::Direction::UP, JET_FORCE);
			jetpack--;
			mander = 'v';
			jet_flag = true;
		}

		// Allows player to jump
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && mover.CanJump(box_mover)) {//box_mover needs to be replaced with an array of all entities. i was thinking of having the array be a binary search tree, that way every time we need to check for collisions (which will probably be every frame) we don't need to iterate through the ENTIRE list.
			mover.Push(Movement::Direction::UP, JUMP_FORCE);
			mander = 'v';
		}


		//------------------------
		//Player Environment
		//------------------------


		// If two objects are close, call a collision
		int temp_x_pos = mover.GetXPos() - box_mover.GetXPos();
		int temp_y_pos = mover.GetYPos() - box_mover.GetYPos();
		if (abs(temp_x_pos) < 20 && abs(temp_y_pos) < 20) {
			ObjectCollision(mover, box_mover);
		}
		

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

		// Recharge Jetpack: Only if jet not used and jetpack isn't fully charged
		if (jetpack < JET_MAX && jet_flag == false) {
			jetpack += 2;
		}

		// Update positions
		mover.UpdatePosition();
		box_mover.UpdatePosition();


		//------------------------
		//Windows managment
		//------------------------


		// Print character to screen 
		jetstring = std::to_string((int)jetpack);

		text.setString(mander);
		text.setPosition(mover.GetXPos(), mover.GetYPos());
		box_text.setPosition(box_mover.GetXPos(), box_mover.GetYPos());

		box_text.setString(box);
		jet_status.setPosition(10, 500);
		jet_status.setString(jetstring);

		window.clear();
		window.draw(text);
		window.draw(box_text);
		window.draw(jet_status);
		window.display();

		if (mover.CanJump(box_mover)) { // changed from mover.GetYPos == 0. this way you can recharge while standing on a dudes head (or a platform).
			jet_flag = false;
		}

	}

	return 0;
}
