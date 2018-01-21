#pragma once

#include "Box2D/Box2D.h"
#include "FWInterface/Component.h"
#include "BaseComponents/Message.h"





class Box2DPhysicsComponent : public Component
{
	
public:
  Box2DPhysicsComponent(std::string name, b2Body * body);
	virtual ~Box2DPhysicsComponent() {};

  virtual void Init();

  virtual void Update() {};

private:

	class RayCast : public b2RayCastCallback {
	public:
		RayCast() {};
		~RayCast() {};
		b2Body * m_body;
		b2Vec2 m_point;
		b2Vec2 m_normal;
	private:
		float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);
	};

protected:
	b2Body * m_body;
  std::map<std::string, b2Joint*> jointMap;


private:
  void GetTransform(bx::Message &msg);
  void SetTransform(bx::Message &msg);
  void ApplyImpulse(bx::Message &msg);
  void ApplyForce(bx::Message &msg);
  void GetBody(bx::Message &msg);
  void CreateRevoluteJoint(bx::Message &msg);
};
