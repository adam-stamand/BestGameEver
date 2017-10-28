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
	void SetMass(float x);
	void SetText(char text);
	float GetXPos();
	float GetYPos();
	float GetXSize();
	float GetYSize();
	float GetMass();
	sf::Text text;
	static sf::Font font;

private:
	float mass;
	float x_pos;
	float y_pos;
	float x_size;
	float y_size;


};

