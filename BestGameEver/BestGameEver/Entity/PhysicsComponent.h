#pragma once
#include "Entity/Component.h"

class PhysicsComponent : public Component
{
public:
	PhysicsComponent(float mass, float gravity, float air_resistance) {
		this->mass = mass;
		this->gravity = gravity;
		this->air_resistance = air_resistance;
		this->ID = PHYSICS;
	};

	virtual ~PhysicsComponent() {};

	//TODO: Consider moving to Component base class
	virtual void Update(EntityBase &entity, sf::RenderWindow &window) {
		this->ApplyAirResistance();
		this->ApplyGravity();

		entity.x_pos += this->x_vel;
		entity.y_pos += this->y_vel;
	}




protected:
	virtual void ApplyAirResistance();
	virtual void ApplyGravity();
	//virtual bool DetectCollision(Entity &entity, Entity &object2);
	//virtual void ObjectCollision(Entity &entity, Entity &object2);
	//virtual void testCollision();


	float y_vel;
	float x_vel;
	float y_accel;
	float x_accel;
	float gravity;
	float air_resistance;
	float mass;



};

