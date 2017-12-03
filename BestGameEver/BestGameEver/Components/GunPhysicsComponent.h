#pragma once

#include "Entity/PhysicsComponentBase.h"
#include "Globals/Globals.h"
#include <stdint.h>
#include "Utils/RateLimiter.h"
#include "Entity/Message.h"
#include "Box2D/Box2D.h"




class GunPhysicsComponent : public PhysicsComponentBase
{
public:

	RateLimiter rateLimiter;
	sf::RenderWindow * window;

	GunPhysicsComponent(b2Body *body, sf::RenderWindow * window) : PhysicsComponentBase(body), window(window), rateLimiter(30) {};
	~GunPhysicsComponent() {};




	class GunRayCast : public b2RayCastCallback {
	public:
		GunRayCast() {};
		~GunRayCast() {};


		b2Fixture* fixture;
		b2Vec2 point;
		b2Vec2 normal;
		float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);
	};



	void Update(EntityInterface &entity) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);
		b2Vec2 bodyPos = this->body->GetPosition();
		float angle = std::atan2((mousePos.y - BOX_2_SF(bodyPos.y)), (mousePos.x - BOX_2_SF(bodyPos.x)));
		this->body->SetTransform(this->body->GetWorldCenter(), angle + 1.571);
	}


	void MessageHandler(ComponentMessage &msg) {
		b2Vec2 unit_vec;
		static int timer = 0;
		switch (msg.funcID) {

		case ComponentMessage::FIRE: {
			if (rateLimiter.Check()) {
				ComponentMessage::Force * params = (ComponentMessage::Force*)msg.params;
				GunRayCast  * gunRay = new GunRayCast;
				unit_vec = this->body->GetWorldVector(b2Vec2(0, 1));
				b2Vec2 point1 = this->body->GetWorldPoint(b2Vec2(0, -1.5));
				b2Vec2 point2 = point1 + (-100.0 * unit_vec);
				Globals::world.RayCast(gunRay, point1, point2);
				gunRay->fixture->GetBody()->ApplyLinearImpulse(params->force * unit_vec, gunRay->point, true);
			}
			break;

		}
		case ComponentMessage::GET_TRANS: {
			ComponentMessage::Transform * params = (ComponentMessage::Transform*)msg.params;
			b2Vec2 temp;
			temp.x = this->body->GetPosition().x;
			temp.y = this->body->GetPosition().y;
			float tempAngle = this->body->GetAngle();
			params->xPos = temp.x;
			params->yPos = temp.y;
			params->angle = tempAngle;

			break;
		}
		}
	}
};

