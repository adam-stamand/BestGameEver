#include "LevelManager.h"

std::vector<Ghost*> LevelManager::ghosts;
std::vector<Item*> LevelManager::items;
std::vector<Structure*> LevelManager::structures;
std::vector<Player*> LevelManager::players;

LevelManager::LevelManager()
{
}


LevelManager::~LevelManager()
{
}


void LevelManager::RegisterPlayer(Player *object) {
	LevelManager::players.push_back(object);
}

void LevelManager::RegisterGhost(Ghost *object) {
	LevelManager::ghosts.push_back(object);
}

void LevelManager::RegisterItem(Item *object) {
	LevelManager::items.push_back(object);
}

void LevelManager::RegisterStructure(Structure *object) {
	LevelManager::structures.push_back(object);
}



void LevelManager::CheckCollisions() {
	for (int i = 0; i < LevelManager::players.size(); i++) {

		for (int j = i+1; j < LevelManager::players.size(); j++) {

			if ((*LevelManager::players.at(i)).CheckCollision((*LevelManager::players.at(j)))) {
				(*LevelManager::players.at(i)).Collision((*LevelManager::players.at(j)));
			}
		}

		for (int j = 0; j < LevelManager::items.size(); j++) {
			if ((*LevelManager::players.at(i)).CheckCollision((*LevelManager::items.at(j)))) {
				(*LevelManager::players.at(i)).Collision((*LevelManager::items.at(j)));
			}
		}

		for (int j = 0; j < LevelManager::structures.size(); j++) {
			if ((*LevelManager::players.at(i)).CheckCollision((*LevelManager::structures.at(j)))) {
				(*LevelManager::players.at(i)).Collision((*LevelManager::structures.at(j)));
			}
		}
	}

	for (int i = 0; i < LevelManager::items.size(); i++) {

		for (int j = i+1; j < LevelManager::items.size(); j++) {
			if ((*LevelManager::items.at(i)).CheckCollision((*LevelManager::items.at(j)))) {
				(*LevelManager::items.at(i)).Collision((*LevelManager::items.at(j)));
			}
		}

		for (int j = 0; j < LevelManager::structures.size(); j++) {
			if ((*LevelManager::items.at(i)).CheckCollision((*LevelManager::structures.at(j)))) {
				(*LevelManager::items.at(i)).Collision((*LevelManager::structures.at(j)));
			}
		}


	}
}


void LevelManager::CheckInput(sf::RenderWindow &window) {

	EventHandler::GetEvents(window);

	for (int i = 0; i < LevelManager::players.size(); i++) {
	
		(*LevelManager::players.at(i)).CheckKeyPressActions((*LevelManager::players.at(i)));
		(*LevelManager::players.at(i)).CheckEventActions((*LevelManager::players.at(i)));

	}

	EventHandler::ClearEvents();

}


void LevelManager::UpdatePositions() {
	for (int i = 0; i < LevelManager::players.size(); i++) {
		(*LevelManager::players.at(i)).UpdatePosition((*LevelManager::players.at(i)));
	}
	for (int i = 0; i < LevelManager::ghosts.size(); i++) {
		(*LevelManager::ghosts.at(i)).UpdatePosition((*LevelManager::ghosts.at(i)));

	}
	for (int i = 0; i < LevelManager::items.size(); i++) {
		(*LevelManager::items.at(i)).UpdatePosition((*LevelManager::items.at(i)));

	}

}

void LevelManager::UpdateScreen(sf::RenderWindow &window) {
	window.clear();
	for (int i = 0; i < LevelManager::players.size(); i++) {
		(*LevelManager::players.at(i)).text.setPosition(((*LevelManager::players.at(i)).GetXPos()), ((*LevelManager::players.at(i)).GetYPos()));
		window.draw((*LevelManager::players.at(i)).text);
	}
	for (int i = 0; i < LevelManager::ghosts.size(); i++) {
		(*LevelManager::ghosts.at(i)).text.setPosition(((*LevelManager::ghosts.at(i)).GetXPos()), ((*LevelManager::ghosts.at(i)).GetYPos()));
		window.draw((*LevelManager::ghosts.at(i)).text);
	}
	for (int i = 0; i < LevelManager::items.size(); i++) {
		(*LevelManager::items.at(i)).text.setPosition(((*LevelManager::items.at(i)).GetXPos()), ((*LevelManager::items.at(i)).GetYPos()));
		window.draw((*LevelManager::items.at(i)).text);
	}
	window.display();
}

