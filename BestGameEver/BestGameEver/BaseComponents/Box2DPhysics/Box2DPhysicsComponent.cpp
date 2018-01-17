#pragma once
#include "BaseComponents/Box2DPhysics/Box2DPhysicsComponent.h"
#include "Factory/Box2DFactory/Box2DFactory.h"

//--TODO--//
// Resolve the body user data issue

Box2DPhysicsComponent::Box2DPhysicsComponent(b2Body * body, std::string name) : Component(name)
{

  // this->m_body = Box2DFactory::CreateBody(fixtures, bodyType);

  // Define another box shape for our dynamic body.
  b2PolygonShape dynamicBox;
  b2Vec2 vec[3];


  vec[0].Set(20, 10);
  vec[1].Set(30, 50);
  vec[2].Set(50, 10);
  dynamicBox.Set(vec, 3);

  // Define the dynamic body fixture.
  b2FixtureDef fixtureDef;
  fixtureDef.shape = &dynamicBox;

  // Set the box density to be non-zero, so it will be dynamic.
  fixtureDef.density = 1.0f;

  // Override the default friction.
  fixtureDef.friction = 3.0f;

  // Add the shape to the body.
  //body->CreateFixture(&fixtureDef);
  this->m_body = body;//Box2DFactory::CreateBody({ &fixtureDef }, bodyType);

  //this->m_body->SetFixedRotation(false);
  // attach entity id to body user data
};


void Box2DPhysicsComponent::Init() {
  SubscribeMessage(&Box2DPhysicsComponent::ApplyImpulse, "ApplyImpulse");
  SubscribeMessage(&Box2DPhysicsComponent::ApplyForce, "ApplyForce");
  SubscribeMessage(&Box2DPhysicsComponent::GetTransform, "GetTransform");
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


float32 Box2DPhysicsComponent::RayCast::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
{
	this->m_body = fixture->GetBody();
	this->m_point = point;
	this->m_normal = normal;
	return fraction;
}






