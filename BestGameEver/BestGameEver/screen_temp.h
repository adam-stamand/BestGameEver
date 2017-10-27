#pragma once
#include <SFML/Graphics.hpp>
#include "Controllable.h"
#include "Movable.h"
#include "Uncontrollable.h"

class screen_temp : public Controllable<screen_temp>
{
public:
	screen_temp();
	~screen_temp();
	void SpawnBox(sf::Event &evnt);
	static std::vector<Movable> level_objects;
	static std::vector<sf::Text> text_objects;
};

