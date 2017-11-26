#pragma once
#include "Factory/ItemType.h"
#include "Factory/UserMaterials.h"
#include "Factory/ItemShape.h"
#include "Globals/Globals.h"



class Rocket : public ItemType {
public:
	Rocket() {
		this->bodyType	=	DYNAMIC_BODY;
		this->itemFixtures	=	
		{
			ItemFixture(
				IMAGE(rocket_ship.png),
				new Steel,
				new PolyItem({ b2Vec2(.5, 0), b2Vec2(1, 0.65), b2Vec2(1, 1), b2Vec2(0, 1), b2Vec2(0, 0.65) }))
		};
	
	}

};

class Box : public ItemType {
public:
	Box() {
		this->bodyType = DYNAMIC_BODY;
		this->itemFixtures =
		{
			ItemFixture(
				IMAGE(box.png),
				new Rubber,
				new PolyItem({ b2Vec2(0, 0), b2Vec2(0,1), b2Vec2(1, 1), b2Vec2(1, 0) }))
		};

	}

};


class Balloon : public ItemType {
public:
	Balloon() {
		this->bodyType = DYNAMIC_BODY;
		this->itemFixtures =
		{
			ItemFixture(
				IMAGE(balloon.png),
				new Rubber,
				new CircleItem(.65, b2Vec2(.5,.35)))
		};

	}

};

class Character : public ItemType {
public:
	Character() {
		this->bodyType = DYNAMIC_BODY;
		this->itemFixtures =
		{
			ItemFixture(
				IMAGE(character.png),
				new Steel,
				new PolyItem({b2Vec2(0,0),b2Vec2(0,1),b2Vec2(1,1),b2Vec2(1,0)}))
		};

	}

};