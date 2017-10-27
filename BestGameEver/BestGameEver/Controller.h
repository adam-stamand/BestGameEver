#pragma once
#include <SFML/Graphics.hpp>
#include "Movable.h"

#define MAX_CONTROLS	50
#define MAX_KEYS		5

class Controller
{
public:
	Controller();
	~Controller();
	//template <typename T>
	void RegisterControl(std::vector<sf::Keyboard::Key> keys, void (Movable::*function)(Movable::Direction, float));

	template <typename T>
	void CheckControl(T object);


private:
	// Struct to hold control information

	struct KeyControl {
		std::vector<sf::Keyboard::Key> keys; //vector of keys; all must be pressed for accerleration to occur
		void (Movable::*function)(Movable::Direction, float);
	};


	std::vector<KeyControl> key_controls; // Vector of KeyControl structs
};

