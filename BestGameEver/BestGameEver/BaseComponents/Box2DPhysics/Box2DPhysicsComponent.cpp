#pragma once
#include "BaseComponents/Box2DPhysics/Box2DPhysicsComponent.h"
#include "Factory/Box2DFactory/Box2DFactory.h"

//--TODO--//
// Resolve the body user data issue

Box2DPhysicsComponent::Box2DPhysicsComponent(std::string name, b2Body * body) : Component(name)
{
  this->m_body  = body;
};


void Box2DPhysicsComponent::Init() {
  SubscribeMessage(&Box2DPhysicsComponent::ApplyImpulse, "ApplyImpulse");
  SubscribeMessage(&Box2DPhysicsComponent::ApplyForce, "ApplyForce");
  SubscribeMessage(&Box2DPhysicsComponent::GetTransform, "GetTransform");
  SubscribeMessage(&Box2DPhysicsComponent::SetTransform, "SetTransform");
  SubscribeMessage(&Box2DPhysicsComponent::CreateRevoluteJoint, "CreateRevoluteJoint");
  SubscribeMessage(&Box2DPhysicsComponent::GetBody, "GetBody");
}

void Box2DPhysicsComponent::ApplyForce(bx::Message &msg) {
  VectorMessage *comp_msg = static_cast<VectorMessage*>(&msg);
  comp_msg->point = flVec2(PIX_2_BOX(comp_msg->point.x), PIX_2_BOX(comp_msg->point.y));
  b2Vec2 unit_vec = this->m_body->GetWorldVector(comp_msg->unitVec);
  this->m_body->ApplyForce((comp_msg->magnitude * unit_vec), this->m_body->GetWorldPoint(comp_msg->point), true);
}


void Box2DPhysicsComponent::ApplyImpulse(bx::Message &msg) {
	VectorMessage *comp_msg = static_cast<VectorMessage*>(&msg);
	b2Vec2 unit_vec = this->m_body->GetWorldVector(comp_msg->unitVec);
  comp_msg->point = flVec2(PIX_2_BOX(comp_msg->point.x), PIX_2_BOX(comp_msg->point.y));
  this->m_body->ApplyLinearImpulse((comp_msg->magnitude * unit_vec), comp_msg->point, true);
}

void Box2DPhysicsComponent::GetTransform(bx::Message &msg) {
  TransformMessage *trans = static_cast<TransformMessage*>(&msg);
  trans->rotation = RAD_2_DEGREES(this->m_body->GetAngle());
  trans->translation = BOX_2_PIX(this->m_body->GetWorldPoint(b2Vec2(0, 0)));
}


void Box2DPhysicsComponent::SetTransform(bx::Message &msg) {
  TransformMessage *trans = static_cast<TransformMessage*>(&msg);
  b2Vec2 temp(PIX_2_BOX(trans->translation.x), PIX_2_BOX(trans->translation.y));
  this->m_body->SetTransform(temp, DEGREES_2_RAD(trans->rotation));
}



void Box2DPhysicsComponent::GetBody(bx::Message &msg) {
  BodyMessage *bodyMsg = static_cast<BodyMessage*>(&msg);
  bodyMsg->body = this->m_body;
}


void Box2DPhysicsComponent::CreateRevoluteJoint(bx::Message &msg) {
  RevoluteJointMessage *jointMsg = static_cast<RevoluteJointMessage*>(&msg);
  Entity * ent = jointMsg->cfg.entityB;
  BodyMessage bodyMsg;
  int rv = PublishMessage(bodyMsg, "GetBody", ent->GetName());
  b2Joint* joint = Box2DFactory::CreateJoint(this->m_body, bodyMsg.body, jointMsg->cfg);
  //this->jointMap.insert(std::pair<std::string, b2Joint*>(jointMsg->name, joint));
}


float32 Box2DPhysicsComponent::RayCast::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
{
	this->m_body = fixture->GetBody();
	this->m_point = point;
	this->m_normal = normal;
	return fraction;
}






