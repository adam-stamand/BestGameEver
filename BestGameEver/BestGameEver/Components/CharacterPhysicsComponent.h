#pragma once

#include "Entity/PhysicsComponentBase.h"
#include "Globals/Globals.h"
#include <stdint.h>
#include "Entity/Message.h"
#include "Utils/RateLimiter.h"


class CharacterPhysicsComponent : public PhysicsComponentBase
{
public:

	RateLimiter rateLimiter;
	CharacterPhysicsComponent(b2Body *body) : PhysicsComponentBase(body), rateLimiter(30) {};
	~CharacterPhysicsComponent();



	class CharacterRayCast : public b2RayCastCallback {
	public:
		CharacterRayCast() {};
		~CharacterRayCast() {};

		b2Fixture* fixture;
		b2Vec2 point;
		b2Vec2 normal;
		float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);
	};

	void MessageHandler(ComponentMessage &msg) {
		b2Vec2 unit_vec;

		switch (msg.funcID) {
		case ComponentMessage::APPLY_FORCE: {
			ComponentMessage::Force * params = (ComponentMessage::Force*)msg.params;
			this->body->ApplyForceToCenter((params->force * params->vec), true);
			break;
		}
		
		case ComponentMessage::FIRE: {
			if (rateLimiter.Check()) {
				ComponentMessage::Force * params = (ComponentMessage::Force*)msg.params;
				CharacterRayCast  * characterRay = new CharacterRayCast;
				unit_vec = this->body->GetWorldVector(params->vec);
				b2Vec2 point1 = this->body->GetWorldPoint(b2Vec2(0, 0));
				b2Vec2 point2 = point1 + (-100.0 * unit_vec);
				Globals::world.RayCast(characterRay, point1, point2);
				characterRay->fixture->GetBody()->ApplyLinearImpulse(params->force * unit_vec, characterRay->point, true);
			}
			break;
		}
		case ComponentMessage::SET_TRANS: {
			ComponentMessage::Transform * params = (ComponentMessage::Transform*)msg.params;
			this->body->SetTransform(b2Vec2(params->xPos, params->yPos), 0);
			this->body->SetAwake(true);
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
	};
};
