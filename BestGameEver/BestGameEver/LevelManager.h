#pragma once
#include <SFML/Graphics.hpp>
#include "EventHandler.h"
#include <vector>
#include "Structure.h"
#include "Ghost.h"
#include "Player.h"
#include "Item.h"


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

	static std::vector<Ghost*> ghosts;
	static std::vector<Player*> players;
	static std::vector<Structure*> structures;
	static std::vector<Item> items;
};
