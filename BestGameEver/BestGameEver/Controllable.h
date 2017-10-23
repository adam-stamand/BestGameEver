#pragma once
#include <SFML/Graphics.hpp>
#include "Movable.h"

#define MAX_CONTROLS	50
#define MAX_KEYS		5

class Controllable : public Movable
{
public:
	Controllable();
	~Controllable();
	
	void RegisterControl(std::vector<sf::Keyboard::Key> keys, Direction dir, float force);
	void CheckControl();

private:
	// Struct to hold control information
	struct KeyControl {
		std::vector<sf::Keyboard::Key> keys; //vector of keys; all must be pressed for accerleration to occur
		Direction dir;	// direction of the  acceleration
		float force; // force to impart on mass
	};

	std::vector<KeyControl> key_controls; // Vector of KeyControl structs
};

