#pragma once
class Movement
{
public:
	Movement(float mass, float max_vel);
	~Movement();

	enum Direction {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	void Push(Direction dir, float force);
	void UpdatePosition();
	float GetXPos();
	float GetYPos();
	float GetXVel();
	float GetYVel();
	void SetXPos(float x);
	void SetYPos(float y);
	void SetXVel(float x);
	void SetYVel(float y);
	float mass;
	float max_vel;
	int Xsize; //delete; just temporary
	int Ysize; //delete

private:
	void ApplyFriction();
	void ApplyGravity();

	float y_vel;
	float x_vel;
	float x_pos;
	float y_pos;
};

