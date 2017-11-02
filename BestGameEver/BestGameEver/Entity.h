#pragma once


#include <SFML/Graphics.hpp>
class Entity
{
public:
	Entity();
	~Entity();


	void SetXPos(float x);
	void SetYPos(float y);
	void SetXSize(float x);
	void SetYSize(float y);
	void SetText(char text);
	void SetMass(float mass);
	void SetXAccel(float x);
	void SetYAccel(float y);
	void SetXVel(float x);
	void SetYVel(float y);

	float GetXVel();
	float GetYVel();
	float GetXAccel();
	float GetYAccel();
	float GetMass();
	float GetXPos();
	float GetYPos();
	float GetXSize();
	float GetYSize();

	void UpdateCollision(Entity &object) { this->collider->Update(*this, object); };
	void UpdateMovement() { this->mover->Update(*this); };
	void UpdateControl() { this->controller->Update(); };


private:
	sf::Text text;
	static sf::Font font;
	float x_pos;
	float y_pos;
	float x_size;
	float y_size;
	float y_vel;
	float x_vel;
	float y_accel;
	float x_accel;
	float mass;

	Controllable *controller;
	MovableComponent *mover;
	CollidableComponent *collider;

};

