
#include <stdio.h>








/*

void Controllable::RegisterControl(std::vector<sf::Keyboard::Key> keys, Direction dir, float force)
{
	// Fill temp struct with user input
	KeyControl temp_control;
	temp_control.keys = keys;
	temp_control.dir = dir;
	temp_control.force = force;

	// Push struct into vector (dynamically sized, so we don't have to worry about it)
	this->key_controls.push_back(temp_control);

	// Debug messages
	printf("Keys registerd. vector size: %d\n", this->key_controls.size());
	printf("Key = %d\n", temp_control.keys.at(0));
}


void Controllable::CheckControl() {

	// Iterate through all KeyControl structs in vector
	for (int i = 0; i < this->key_controls.size(); i++) {

		KeyControl temp_control = key_controls.at(i); //Grab one KeyControl struct
		bool skip = false; //initialize

		for (int j = 0; j < temp_control.keys.size(); j++) { // iterate through all keys in struct
			if (!sf::Keyboard::isKeyPressed(temp_control.keys.at(j))) {
				skip |= true; // if any keys are not pressed, OR skip with true;
			}
		}

		if (!skip) { // if skip is still false, meaning all keys were pressed, execute acceleration
			this->Accelerate(temp_control.dir, temp_control.force);
		}

	}


*/