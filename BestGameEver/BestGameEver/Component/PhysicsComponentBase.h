#pragma once

#include "Box2D/Box2D.h"
#include "Component/ComponentBase.h"

// Breakout base components to cpp files

class PhysicsComponentBase : public ComponentBase
{
public:
	PhysicsComponentBase(Item * item) : ComponentBase(PHYSICS){
		this->body = item->body;
		// attach entity id to body user data
	};
	virtual ~PhysicsComponentBase() {};
	
	
	void Update() {ComponentUpdate();}
	void MessageHandler(ComponentMessage &msg) {

		switch (msg.funcID) {

		case ComponentMessage::GET_TRANSFORM: {
			ComponentMessage::Transform * params = (ComponentMessage::Transform*)msg.params;
			params->xPos = this->body->GetPosition().x;
			params->yPos = this->body->GetPosition().y;
			params->angle = this->body->GetAngle();
			break;
		}

		case ComponentMessage::GET_BODY: {
			b2Body ** body = (b2Body**)msg.params;
			*body = this->body;
			break;
		}

		case ComponentMessage::SET_TRANSFORM: {
			ComponentMessage::Transform * params = (ComponentMessage::Transform*)msg.params;
			this->body->SetTransform(b2Vec2(params->xPos, params->yPos), params->angle);
			this->body->SetAwake(true);
			break;
		}

		case ComponentMessage::ENABLE_BODY: {
			bool * state = (bool*)msg.params;
			this->body->SetActive(*state);
			break;
		}

		case ComponentMessage::APPLY_FORCE: {
			ComponentMessage::Force * params = (ComponentMessage::Force*)msg.params;
			b2Vec2 unit_vec = this->body->GetWorldVector(params->vec);
			this->body->ApplyForce((params->force * unit_vec), this->body->GetWorldPoint(params->point), true);
			break;
		}

		case ComponentMessage::APPLY_IMPULSE: {
			ComponentMessage::Force * params = (ComponentMessage::Force*)msg.params;
			b2Vec2 unit_vec = this->body->GetWorldVector(params->vec);
			this->body->ApplyLinearImpulse((params->force * unit_vec), this->body->GetWorldPoint(params->point), true);
			break;
		}

		}
		ComponentMessageHandler(msg);
	}


	virtual void ComponentMessageHandler(ComponentMessage &msg) {};
	virtual void ComponentUpdate() {};



	class PhysicsRayCast : public b2RayCastCallback {
	public:
		PhysicsRayCast() {};
		~PhysicsRayCast() {};

		b2Fixture* fixture;
		b2Vec2 point;
		b2Vec2 normal;
		float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
		{
			this->fixture = fixture;
			this->point = point;
			this->normal = normal;
			return fraction;
		}
	};


protected:

	b2Body *body;
};

