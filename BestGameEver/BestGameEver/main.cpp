#include <SFML/Graphics.hpp>
#include <string> 

using namespace sf;

#define VEL_MAX		.1
#define FRICTION	0.0005  // must be less than 1... or else you get like negative friction
#define FORCE		0.0001
#define GRAVITY		0.00009
#define JUMP_FORCE	0.25
#define JET_MAX		100000
#define JET_FORCE	0.00025
#define MASS		1.4




class Movement {
public:
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

// Ellastic Collision
template <typename T1, typename T2>
void ObjectCollision(T1 &object1, T2 &object2) {

	{
		object1.SetXVel(
			(((object1.mass - object2.mass) / (object1.mass + object2.mass)) * object1.GetXVel()) +
			(((2 * object2.mass) / (object1.mass + object2.mass)) * object2.GetXVel())
		);

		object2.SetXVel(
			(((object2.mass - object1.mass) / (object1.mass + object2.mass)) * object2.GetXVel()) +
			(((2 * object1.mass) / (object1.mass + object2.mass)) * object1.GetXVel())
		);

		object1.SetYVel(
			(((object1.mass - object2.mass) / (object1.mass + object2.mass)) * object1.GetYVel()) +
			(((2 * object2.mass) / (object1.mass + object2.mass)) * object2.GetYVel())
		);

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
}
template <typename T1>
void BoundaryYCollision(T1 &object) {
	object.SetYVel(-object.GetYVel() * 0.8);
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && mover.GetYPos() <= 0) {
			mover.Push(Movement::Direction::UP, JUMP_FORCE);
			mander = 'v';
		}


		//------------------------
		//Player Environment
		//------------------------


		// If two objects are close, call a collision
		int temp_x_pos = mover.GetXPos() - box_mover.GetXPos();
		int temp_y_pos = mover.GetYPos() - box_mover.GetYPos();
		int temp;
		if (abs(temp_x_pos) < 20 && abs(temp_y_pos) < 20) {
			ObjectCollision(mover, box_mover);

			// Workaround to prevent objects from getting stuck inside eachother
			if (temp_y_pos > 15) {
				

				if (temp_y_pos <= 0) { // if player below
					temp = std::min((int)box_mover.GetYPos() + (20 - abs(temp_y_pos)), 580);
					box_mover.SetYPos(temp);
					if (temp == 580) {
						mover.SetYPos(560);
					}

				}
				else {
					temp = std::max((int)box_mover.GetYPos() - (20 - abs(temp_y_pos)), 0);
					box_mover.SetYPos(temp); 
					if (temp == 0) {
						mover.SetYPos(21);
					}
				}
			}
			else {
				if (temp_x_pos <= 0) { // if player on left
					temp = std::min((int)box_mover.GetXPos() + (20 - abs(temp_x_pos)), 780);
					box_mover.SetXPos(temp); // push box to right 
					if (temp == 780) {
						mover.SetXPos(760);
					}
				}
				else {
					temp = std::max((int)box_mover.GetXPos() - (20 - abs(temp_x_pos)), 0);
					box_mover.SetXPos(temp); // else push box to left
					if (temp == 0) {
						mover.SetXPos(20);
					}
				}
			}
		}

		// If either object gets close to border, call boundary collision
		if ((box_mover.GetXPos() < 0 && box_mover.GetXVel() < 0) || (box_mover.GetXPos() > 780 && box_mover.GetXVel() > 0)) {
			BoundaryXCollision(box_mover);
		}
		if ((mover.GetXPos() <= 0 && mover.GetXVel() < 0) || (mover.GetXPos() >= 780 && mover.GetXVel() > 0)) {
			BoundaryXCollision(mover);
		}
		if ((mover.GetYPos() <= 0 && mover.GetYVel() < 0) || (mover.GetYPos() >= 580 && mover.GetYVel() > 0)) {
			BoundaryYCollision(mover);
		}
		if ((box_mover.GetYPos() <= 0 && box_mover.GetYVel() < 0) || (box_mover.GetYPos() >= 580 && box_mover.GetYVel() > 0)) {
			BoundaryYCollision(box_mover);
		}

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

		if (mover.GetYPos() <= 0) {
			jet_flag = false;
		}

	}

	return 0;
}
