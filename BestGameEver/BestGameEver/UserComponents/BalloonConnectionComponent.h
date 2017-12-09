#pragma once

#include "Component/ConnectionComponentBase.h"
#include "Manager/EntityManager.h"

// move to generic component

class BalloonConnectionComponent : public ConnectionComponentBase 
{
public:


	BalloonConnectionComponent(uint32_t vehicleID, uint32_t occupantID) : ConnectionComponentBase() {
		this->vehicleID = vehicleID;
		this->occupantID = occupantID;
	};

	~BalloonConnectionComponent() {};


	bool occupied = false;
	bool inRange = false;
	uint32_t vehicleID;
	uint32_t occupantID;
	b2RevoluteJointDef jointDef;
	b2RevoluteJoint* m_joint;
	void ComponentMessageHandler(ComponentMessage &msg) {

		switch (msg.funcID) {


		case ComponentMessage::GET_IDS: {
			ComponentMessage::Contact * params = (ComponentMessage::Contact*)msg.params;
			params->idVec = { this->vehicleID, this->occupantID };

			break;
		}

		case ComponentMessage::CONTACT_BEGIN: {
			this->inRange = true;
			break;
		}

		case ComponentMessage::CONTACT_END: {
			this->inRange = false;
			break;
		}
		case ComponentMessage::ENTER: {
			if (this->occupied) {

				m_joint->GetBodyA()->SetGravityScale(2);
				Globals::world.DestroyJoint(this->m_joint);
				this->m_joint = NULL;
				this->occupied = false;
			}
			else if (this->inRange) {

				b2Body * tempBody;
				ComponentMessage comp_msg(PHYSICS, ComponentMessage::GET_BODY, &tempBody);

				EntityManager::SendMessage(this->vehicleID, comp_msg);
				jointDef.bodyA = tempBody;
				tempBody->SetGravityScale(-10);
				EntityManager::SendMessage(this->occupantID, comp_msg); // TODO Needs to be double checked
				jointDef.bodyB = tempBody;

				jointDef.collideConnected = false;
				jointDef.localAnchorA.Set(0, .75);
				jointDef.localAnchorB.Set(0, -.5);
				this->m_joint = (b2RevoluteJoint*)Globals::world.CreateJoint(&jointDef);

				this->occupied = true;
			}

			break;
		}
		}
	}


};