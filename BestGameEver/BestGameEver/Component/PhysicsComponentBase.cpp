#pragma once
#include "Component/PhysicsComponentBase.h"


PhysicsComponentBase::PhysicsComponentBase(Item * item) : ComponentBase(PHYSICS){
	this->body = item->body;
	// attach entity id to body user data
};

	

void PhysicsComponentBase::Update() {
	ComponentUpdate();
}

void PhysicsComponentBase::MessageHandler(ComponentMessage &msg) {

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


float32 PhysicsComponentBase::PhysicsRayCast::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
{
	this->fixture = fixture;
	this->point = point;
	this->normal = normal;
	return fraction;
}




