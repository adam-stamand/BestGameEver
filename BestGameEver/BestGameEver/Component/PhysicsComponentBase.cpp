#pragma once
#include "Component/PhysicsComponentBase.h"


//--TODO--//
// Resolve the body user data issue
// use return value to determine whether to override following switch


void PhysicsComponentBase::MessageHandler(ComponentMessage &msg) {
	//std::map<std::string, void(PhysicsComponentBase::*)(ComponentMessage &comp_msg)> tempmap({
	//	{ "APPLY_FORCE", &PhysicsComponentBase::ApplyForceMessageHandler },
	//	{ "APPLY_IMPULSE", &PhysicsComponentBase::ApplyImpulseMessageHandler },
	//	{ "GET_ITEM", &PhysicsComponentBase::GetItemMessageHandler },
	//	{ "TRANSFORM", &PhysicsComponentBase::TransformMessageHandler }
	//});
	//(this->*tempmap.find(msg.funcName)->second)(msg);
	(this->*messageHandlerMap.find(msg.funcName)->second)(msg);
}

PhysicsComponentBase::PhysicsComponentBase(Item * item) : ComponentBase(PHYSICS),
	messageHandlerMap({
	{ "APPLY_FORCE", &PhysicsComponentBase::ApplyForceMessageHandler },
	{ "APPLY_IMPULSE", &PhysicsComponentBase::ApplyImpulseMessageHandler },
	{ "GET_ITEM", &PhysicsComponentBase::GetItemMessageHandler },
	{ "TRANSFORM", &PhysicsComponentBase::TransformMessageHandler }
	})
{
	this->m_item = item;
	// attach entity id to body user data
};

	
void PhysicsComponentBase::Update() {
	ComponentUpdate(); // use return value to determine whether to override following switch
}


void PhysicsComponentBase::GetItemMessageHandler(ComponentMessage &comp_msg) {
	ItemMessage *itemMessage = static_cast<ItemMessage*>(&comp_msg);
	itemMessage->item = this->m_item;
}

void PhysicsComponentBase::TransformMessageHandler(ComponentMessage &comp_msg) {
	TransformMessage *transMessage = static_cast<TransformMessage*>(&comp_msg);
	if (transMessage->GetDirection() == ComponentMessage::INPUT) {
		this->m_item->body->SetTransform(transMessage->center, transMessage->angle);
	}
	else {
		transMessage->center = this->m_item->body->GetWorldPoint(b2Vec2(0, 0));
		transMessage->angle = this->m_item->body->GetAngle();
		this->m_item->body->SetAwake(true);
	}	
}

/*
void PhysicsComponentBase::EnableBody(ComponentMessage &comp_msg) {
	TransformMessage *transMessage = static_cast<TransformMessage*>(&comp_msg);
	bool * state = (bool*)msg.params;
	this->body->SetActive(*state);
}
*/

void PhysicsComponentBase::ApplyForceMessageHandler(ComponentMessage &comp_msg) {
	ForceMessage *forceMessage = static_cast<ForceMessage*>(&comp_msg);
	b2Vec2 unit_vec = this->m_item->body->GetWorldVector(forceMessage->unitVec);
	this->m_item->body->ApplyForce((forceMessage->magnitude * unit_vec), this->m_item->body->GetWorldPoint(forceMessage->point), true);
}

void PhysicsComponentBase::ApplyImpulseMessageHandler(ComponentMessage &comp_msg) {
	ImpulseMessage *impulseMessage = static_cast<ImpulseMessage*>(&comp_msg);
	b2Vec2 unit_vec = this->m_item->body->GetWorldVector(impulseMessage->unitVec);
	this->m_item->body->ApplyLinearImpulse((impulseMessage->magnitude * unit_vec), this->m_item->body->GetWorldPoint(impulseMessage->point), true);
}


float32 PhysicsComponentBase::PhysicsRayCast::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
{
	this->m_item.body = fixture->GetBody();
	this->m_point = point;
	this->m_normal = normal;
	return fraction;
}




