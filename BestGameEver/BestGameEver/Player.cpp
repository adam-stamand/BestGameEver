#include "Player.h"

Player::Player()
{
}


Player::~Player()
{
}




void Player::MoveUp() { this->Accelerate(Movable::Direction::UP, -FORCE, *this); }
void Player::MoveDown() { this->Accelerate(Movable::Direction::DOWN, -FORCE, *this); }
void Player::MoveRight() { this->Accelerate(Movable::Direction::RIGHT, FORCE, *this); }
void Player::MoveLeft() { this->Accelerate(Movable::Direction::LEFT, FORCE, *this); }
void Player::Quit(sf::Event &evnt) { if (evnt.key.code == sf::Keyboard::Escape) puts("WUIT"); }


