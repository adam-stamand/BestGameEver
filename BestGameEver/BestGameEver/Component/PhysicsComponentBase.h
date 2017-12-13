#pragma once

#include "Box2D/Box2D.h"

#include "Component/ComponentBase.h"
#include "Factory/Item.h"


class PhysicsComponentBase : public ComponentBase
{
public:
	PhysicsComponentBase(Item * item);
	virtual ~PhysicsComponentBase() {};
	
	void Update();
	void MessageHandler(ComponentMessage &msg);
	virtual void ComponentMessageHandler(ComponentMessage &msg) {};
	virtual void ComponentUpdate() {};

	class PhysicsRayCast : public b2RayCastCallback {
	public:
		PhysicsRayCast() {};
		~PhysicsRayCast() {};

		b2Fixture* fixture;
		b2Vec2 point;
		b2Vec2 normal;
		float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);
	};

protected:
	b2Body *body;
};

