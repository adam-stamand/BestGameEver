#pragma once
#include <SFML/Graphics.hpp>
#include "EventHandler.h"
#include <vector>


class LevelManager
{
public:
	LevelManager();
	~LevelManager();

	static void LevelManager::RegisterPlayer(Player *object);
	static void LevelManager::RegisterGhost(Ghost *object);
	static void LevelManager::RegisterItem(Item object);
	static void LevelManager::RegisterStructure(Structure *object);


	static void CheckCollisions();
	static void CheckInput(sf::RenderWindow &window);
	static void UpdateScreen(sf::RenderWindow &window);
	static void UpdatePositions();

};
