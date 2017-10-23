#pragma once
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
	float GetXPos();
	float GetYPos();
	float GetXSize();
	float GetYSize();
	float GetMass();


private:
	float mass;
	float x_pos;
	float y_pos;
	float x_size;
	float y_size;


};

