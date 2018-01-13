#pragma once

#include <stdint.h>
#include "Component/PhysicsComponentBase.h"
#include "Globals/Globals.h"
#include "Utils/RateLimiter.h"
#include "Factory/Factory.h"


class GunPhysicsComponent : public PhysicsComponentBase
{
public:

	RateLimiter rateLimiter;
	sf::RenderWindow * window;

	GunPhysicsComponent(Item * item, sf::RenderWindow * window) : PhysicsComponentBase(item), window(window), rateLimiter(30) {};
	~GunPhysicsComponent() {};



	void ComponentUpdate() {
		sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);
		b2Vec2 bodyPos = this->m_item->body->GetPosition();
		float angle = std::atan2((mousePos.y - BOX_2_SF(bodyPos.y)), (mousePos.x - BOX_2_SF(bodyPos.x)));
		this->m_item->body->SetTransform(this->m_item->body->GetWorldPoint(b2Vec2(0,0)), angle + 1.571);
	}


};

