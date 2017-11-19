#pragma once
#include "Factory/ItemType.h"

class Item {

public:
	Item() {};

	std::vector<sf::Sprite *> sprites;
	b2Body * body;

};
