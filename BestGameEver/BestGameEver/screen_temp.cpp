#include "screen_temp.h"



std::vector<Movable> screen_temp::level_objects;
std::vector<sf::Text> screen_temp::text_objects;

screen_temp::screen_temp()
{
}


screen_temp::~screen_temp()
{
}



void screen_temp::SpawnBox(sf::Event &evnt) {
	

	sf::Text temp_text;
	temp_text.setString("0");
	temp_text.setCharacterSize(40);

	Uncontrollable temp;
	temp.SetMass(.5);
	temp.SetXPos(evnt.mouseButton.x);
	temp.SetYPos(evnt.mouseButton.y);
	temp.SetXVel(0);
	temp.SetYVel(0);
	temp.SetXSize(20);
	temp.SetYSize(20);


	screen_temp::level_objects.push_back(temp);
	screen_temp::text_objects.push_back(temp_text);
}
