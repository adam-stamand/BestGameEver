#include "MainCharacter.h"



MainCharacter::MainCharacter()
{
}


MainCharacter::~MainCharacter()
{
}

void MainCharacter::MoveUp() { this->Accelerate(Movable::Direction::UP, -FORCE, *this); }
void MainCharacter::MoveDown() { this->Accelerate(Movable::Direction::DOWN, -FORCE, *this); }
void MainCharacter::MoveRight() { this->Accelerate(Movable::Direction::RIGHT, FORCE, *this); }
void MainCharacter::MoveLeft() { this->Accelerate(Movable::Direction::LEFT, FORCE, *this); }
void MainCharacter::Quit(sf::Event &evnt) { if (evnt.key.code == sf::Keyboard::Escape) puts("WUIT"); }


void MainCharacter::SpawnBox(sf::Event &evnt) {
	if (evnt.mouseButton.button == 0) {
		Item i;
		i.SetXPos(evnt.mouseButton.x);
		i.SetYPos(evnt.mouseButton.y);
		i.SetText('B');
		LevelManager::RegisterItem(i);
	}

}