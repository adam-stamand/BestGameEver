#pragma once
#include "Controllable.h"
#include "Movable.h"
#include "Entity.h"
#include "Collidable.h"


class Player : public Entity
{
public:
	Player();
	~Player();

	void UpdateCollision(Entity &object) { this->collidable.Update(*this, object); };
	void UpdateMovement() { this->movable.Update(*this); };
	void UpdateControl() { this->controller.Update(*this); };



private:
	Movable movable;
	Collidable collidable;
	Controllable<Player> controller;


	void MoveUp() { movable.Accelerate(Movable::Direction::UP, -FORCE, *this); }
	void MoveDown() { movable.Accelerate(Movable::Direction::DOWN, -FORCE, *this); }
	void MoveRight() { movable.Accelerate(Movable::Direction::RIGHT, FORCE, *this); }
	void MoveLeft() { movable.Accelerate(Movable::Direction::LEFT, FORCE, *this); }
	void Quit(sf::Event &evnt) { if (evnt.key.code == sf::Keyboard::Escape) puts("WUIT"); }

};

