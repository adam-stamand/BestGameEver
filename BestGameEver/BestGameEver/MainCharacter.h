#pragma once
#include "Player.h"
#include "LevelManager.h"

class MainCharacter : public Player
{
public:
	MainCharacter();
	~MainCharacter();
	void MoveUp();
	void MoveRight();
	void MoveLeft();
	void MoveDown();
	void Quit(sf::Event &evnt);
	void SpawnBox(sf::Event &evnt);
};

