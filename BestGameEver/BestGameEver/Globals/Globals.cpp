#include "Globals/Globals.h"

b2World Globals::world(b2Vec2(0.0, 4.0));
uint32_t Globals::globalTimer = 0;
uint32_t Globals::idCounter = 0;



uint32_t Globals::GetID()		{ return Globals::idCounter++; }
uint32_t Globals::GetTimer()	{ return Globals::globalTimer; }
void Globals::IncrTimer()		{ Globals::globalTimer++; }

