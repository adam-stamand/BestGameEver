#include "Globals/Globals.h"

b2World Globals::world(b2Vec2(0.0, 4.0));
uint32_t Globals::globalTimer = 0;
uint32_t Globals::entityIDCounter = 1;
uint32_t Globals::componentIDCounter = 1;
sf::RenderWindow Globals::window(sf::VideoMode(800, 600), "Best Game Ever", sf::Style::Default);
EntityFactoryInterface * Globals::entFactoryInterface = NULL;


uint32_t Globals::GetEntityID() { 
	uint32_t temp = Globals::entityIDCounter;
	Globals::entityIDCounter = (Globals::entityIDCounter % 0xFFFFFFFF) + 1; // consider cost of modulo? - Prevent 0; Invalid ID
	return temp;
}

uint32_t Globals::GetComponentID()		{ return Globals::componentIDCounter++; }
uint32_t Globals::GetTimer()			{ return Globals::globalTimer; }
void Globals::IncrTimer()				{ Globals::globalTimer++; }

