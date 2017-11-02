#include "Entity.h"

sf::Font Entity::font;

Entity::Entity()
{
	text.setString(">");
	text.setCharacterSize(50);
	text.setPosition(40, 40);
	Entity::font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
	text.setFont(Entity::font);
}


Entity::~Entity()
{
}






// Setters
void Entity::SetText(char text) {
	this->text.setString(text);
}

void Entity::SetXPos(float x) {
	this->x_pos = x;
}

void Entity::SetYPos(float y) {
	this->y_pos = y;
}


void Entity::SetYVel(float y) {
	this->y_vel = y;
}


void Entity::SetXVel(float x) {
	this->x_vel = x;
}


void Entity::SetYAccel(float y) {
	this->y_accel = y;
}


void Entity::SetXAccel(float x) {
	this->x_accel = x;
}


void Entity::SetMass(float mass) {
	this->mass = mass;
}


void Entity::SetXSize(float x) {
	this->x_size = x;
}


void Entity::SetYSize(float y) {
	this->y_size = y;
}


// Getters
float Entity::GetXPos() {
	return this->x_pos;
}

float Entity::GetYPos() {
	return this->y_pos;
}

float Entity::GetXVel() {
	return this->x_vel;
}


float Entity::GetYVel() {
	return this->y_vel;
}

float Entity::GetXAccel() {
	return this->x_accel;
}


float Entity::GetYAccel() {
	return this->y_accel;
}


float Entity::GetXSize() {
	return this->x_size;
}

float Entity::GetYSize() {
	return this->y_size;
}

float Entity::GetMass() {
	return this->mass;
}


