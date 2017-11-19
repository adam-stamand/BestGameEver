#pragma once
#include "Factory/ItemType.h"
#include "Factory/UserMaterials.h"



class Rocket : public ItemType {
public:
	Rocket() {
		this->bodyType	=	DYNAMIC_BODY;
		this->fixtures	=	
		{
			ItemFixture(
				IMAGE(rocket_ship.png),
				POLYGON,
				new Steel,
				{ b2Vec2(.5, 0), b2Vec2(1, 0.65), b2Vec2(1, 1), b2Vec2(0, 1), b2Vec2(0, 0.65) })
		};
	
	}

};

class Box : public ItemType {
public:
	Box() {
		this->bodyType = DYNAMIC_BODY;
		this->fixtures =
		{
			ItemFixture(
				IMAGE(box.png),
				POLYGON,
				new Wood,
				{ b2Vec2(0, 0), b2Vec2(0,1), b2Vec2(1, 1), b2Vec2(1, 0) })
		};

	}

};