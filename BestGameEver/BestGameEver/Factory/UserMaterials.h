#pragma once
#include "Factory/Material.h"


class Steel : public Material {

public:
	Steel() {
		this->density		=	5.0f;
		this->friction		=	25.0f;
		this->resitution	=	.1f;
	};

};

class Wood : public Material {

public:
	Wood() {
		this->density = 2.0f;
		this->friction = 30.0f;
		this->resitution = .25f;
	};

};

