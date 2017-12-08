#pragma once
#include "Factory/ItemType.h"
#include "Factory/UserMaterials.h"
#include "Factory/ItemShape.h"
#include "Globals/Globals.h"



class Rocket : public ItemType {
public:
	Rocket() {
		this->bodyType	=	DYNAMIC_BODY;
		this->file		=	IMAGE(rocket_ship.png);
		this->material	=	new Steel;
		this->shape		=	new PolyItem({ b2Vec2(.5, 0), b2Vec2(1, 0.65), b2Vec2(1, 1), b2Vec2(0, 1), b2Vec2(0, 0.65) });
	}

};

class Box : public ItemType {
public:
	Box() {
		this->bodyType = DYNAMIC_BODY;
		this->file = IMAGE(box.png);
		this->material = new Wood;
		this->shape = new PolyItem({ b2Vec2(0, 0), b2Vec2(0,1), b2Vec2(1, 1), b2Vec2(1, 0) });
	}

};


class Balloon : public ItemType {
public:
	Balloon() {
		this->bodyType = DYNAMIC_BODY;
		this->file = IMAGE(balloon.png);
		this->material = new Rubber;
		this->shape = new CircleItem(.65, b2Vec2(0, -.25));
	}

};

class Character : public ItemType {
public:
	Character() {
		this->bodyType = DYNAMIC_BODY;
		this->file = IMAGE(character.png);
		this->material = new Wood;
		this->shape = new PolyItem({ b2Vec2(0,0),b2Vec2(0,1),b2Vec2(1,1),b2Vec2(1,0) });
		
	}

};


class Cannon : public ItemType {
public:
	Cannon() {
		this->bodyType = DYNAMIC_BODY;
		this->file = IMAGE(cannon.png);
		this->material = new Rubber;
		this->shape = new PolyItem({ b2Vec2(0,0),b2Vec2(0,1),b2Vec2(1,1),b2Vec2(1,0) });

	}

};

class Tire : public ItemType {
public:
	Tire() {
		this->bodyType = DYNAMIC_BODY;
		this->file = IMAGE(tire.png);
		this->material = new Rubber;
		this->shape = new CircleItem(1, b2Vec2(0,0));

	}

};

class Tree : public ItemType {
public:
	Tree() {
		this->bodyType = DYNAMIC_BODY;
		this->file = IMAGE(tree.png);
		this->material = NULL;
		this->shape = NULL;
	}

};

class Background : public ItemType {
public:
	Background() {
		this->bodyType = DYNAMIC_BODY;
		this->file = IMAGE(sky_background.png);
		this->material = NULL;
		this->shape = NULL;
	}

};