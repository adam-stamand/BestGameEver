#pragma once
#include "Factory/ItemType.h"
#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"


#define DYNAMIC_BODY	b2BodyType::b2_dynamicBody
#define STATIC_BODY		b2BodyType::b2_staticBody
#define KINEMATIC_BODY	b2BodyType::b2_kinematicBody



class Part
{

public:
	friend class Factory;
	sf::Sprite * GetSprite() { return this->sprite; };
	b2Vec2 * GetCenter() { return &this->center; };
	float * GetAngle() { return &this->angle; };

private:
	Part() {}
	b2FixtureDef * fixtureDef;
	sf::Sprite * sprite;
	b2Vec2 center;
	float angle;
};


class Item {

public:
	Item() {};
	
	b2Vec2 GetTranslation() {
		if (this->body != NULL) {
			return this->body->GetWorldPoint(b2Vec2(0,0));
		}
		else {
			return b2Vec2(0,0);
		}
	}

	float GetAngle() {
		if (this->body != NULL) {
			return this->body->GetAngle();
		}
		else {
			return 0;
		}
	}

	void SetCenterMass(b2Vec2 localPoint) {
		b2MassData massD;
		this->body->GetMassData(&massD);
		massD.center.Set(localPoint.x, localPoint.y);
		this->body->SetMassData(&massD);
	}

	std::vector<Part*> parts;
	//b2Body * GetBody() { return this->body; }

	b2Body * body = NULL;


private:
	

};