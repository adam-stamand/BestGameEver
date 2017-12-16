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


	void ComponentMessageHandler(ComponentMessage &msg) {
		/*
		switch (msg.funcID) {

		case ComponentMessage::FIRE: {
			if (rateLimiter.Check()) {
				PhysicsRayCast ray;
				ComponentMessage::Force * params = (ComponentMessage::Force*)msg.params;
				b2Vec2 unit_vec = this->body->GetWorldVector(b2Vec2(0, 1));
				b2Vec2 point1 = this->body->GetWorldPoint(b2Vec2(0, -1.5));
				b2Vec2 point2 = point1 + (-100.0 * unit_vec);
				Globals::world.RayCast(&ray, point1, point2);
				ray.fixture->GetBody()->ApplyLinearImpulse(params->force * unit_vec, ray.point, true);
			}
			break;

		}
		}
		*/
	}
};

