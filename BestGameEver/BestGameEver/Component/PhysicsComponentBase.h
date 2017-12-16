#pragma once

#include "Box2D/Box2D.h"
#include "Factory/Item.h"
#include "Component/ComponentBase.h"
#include "Factory/Item.h"
#include "Utils/StringHash.h"

//--TODO--//
// Make component independent of body definition

class PhysicsComponentBase : public ComponentBase
{
	typedef void(PhysicsComponentBase::*MessageHandler_p)(ComponentMessage &comp_msg);

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
		Item m_item;
		b2Vec2 m_point;
		b2Vec2 m_normal;
	private:
		float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);
	};

protected:
	Item * m_item;
	float m_xPos = 0; // move into item?
	float m_yPos = 0;
	float m_angle = 0;


private:
	std::map<std::string, MessageHandler_p> messageHandlerMap;
	void GetItemMessageHandler(ComponentMessage &comp_msg);
	void TransformMessageHandler(ComponentMessage &comp_msg);
	//void EnableBody(ComponentMessage &comp_msg);
	void ApplyForceMessageHandler(ComponentMessage &comp_msg);
	void ApplyImpulseMessageHandler(ComponentMessage &comp_msg);
};

