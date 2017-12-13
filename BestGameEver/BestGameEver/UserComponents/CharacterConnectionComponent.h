#pragma once

#include "Component/ConnectionComponentBase.h"
#include "Manager/EntityManager.h"

// move to generic component

class CharacterConnectionComponent : public ConnectionComponentBase
{

public:


	enum CharacterConnection {
		ROCKET_CONNECTION,
		CAR_CONNECTION,
		BALLOON_CONNECTION,
		GUN_CONNECTION,
		SEGMENT_CONNECTION,
		NUM_CONNECTION
	};



	CharacterConnectionComponent(std::vector<uint32_t> entityIDs) : ConnectionComponentBase(entityIDs) {
		this->entityIDs = entityIDs;

		EntityManager::DisableComponent(entityIDs[ROCKET_CONNECTION], CONTROLS);
		EntityManager::DisableComponent(entityIDs[GUN_CONNECTION], CONTROLS);
		EntityManager::DisableComponent(entityIDs[GUN_CONNECTION], PHYSICS);
		EntityManager::DisableComponent(entityIDs[CAR_CONNECTION], CONTROLS);

	};

	~CharacterConnectionComponent() {};


	
	bool touchingRocket = false;
	bool touchingBalloon = false;
	bool touchingCar = false;
	bool inCar = false;
	bool inBalloon = false;
	bool inRocket = false;
	bool onGround = false;
	bool occupied = false;
	b2RevoluteJointDef jointDef;
	b2RevoluteJoint* m_joint;

	void BeginContact(uint32_t id) {
		if (id == this->entityIDs[ROCKET_CONNECTION]) {
			touchingRocket = true;
		}
		else if (id == this->entityIDs[BALLOON_CONNECTION]) {
			touchingBalloon = true;
		}
		else if (id == this->entityIDs[CAR_CONNECTION]) {
			touchingCar = true;
		}
	}


	void EndContact(uint32_t id) {
		
		if (id == this->entityIDs[ROCKET_CONNECTION]) {
			touchingRocket = false;
		}
		else if (id == this->entityIDs[BALLOON_CONNECTION]) {
			touchingBalloon = false;
		}
		else if (id == this->entityIDs[CAR_CONNECTION]) {
			touchingCar = false;
		}
	}

	void ComponentMessageHandler(ComponentMessage &msg) {

		switch (msg.funcID) {

		case ComponentMessage::JUMP: {
			if (onGround) {
				ComponentMessage comp_msg(PHYSICS, ComponentMessage::APPLY_IMPULSE, msg.params);
				EntityManager::SendMessage(this->GetEntityID(), comp_msg);
			}

			break;
		}


		case ComponentMessage::ENTER: {
			if (this->occupied) {
				
				if (this->inBalloon) {
					this->inBalloon = false;
					b2Body * tempBody;
					ComponentMessage comp_msg(PHYSICS, ComponentMessage::GET_BODY, &tempBody);
					EntityManager::SendMessage(this->entityIDs[BALLOON_CONNECTION], comp_msg);
					tempBody->SetGravityScale(2);
					Globals::world.DestroyJoint(this->m_joint);
					this->m_joint = NULL;
					this->occupied = false;
				}
				else if (this->inCar){
					EntityManager::DisableComponent(entityIDs[CAR_CONNECTION], CONTROLS);
					EntityManager::EnableComponent(this->GetEntityID(), PHYSICS);
					EntityManager::EnableComponent(this->GetEntityID(), GRAPHICS);

					ComponentMessage::Transform trans;
					ComponentMessage comp_msg(PHYSICS, ComponentMessage::GET_TRANSFORM, &trans);
					EntityManager::SendMessage(entityIDs[CAR_CONNECTION], comp_msg);

					b2Body * tempBody;
					ComponentMessage comp_msg2(PHYSICS, ComponentMessage::GET_BODY, &tempBody);
					EntityManager::SendMessage(this->GetEntityID(), comp_msg2);
					tempBody->SetActive(true);

					trans.angle = 0; // we don't want to rotate the character
					comp_msg.funcID = ComponentMessage::SET_TRANSFORM;
					EntityManager::SendMessage(this->GetEntityID(), comp_msg);
					this->inCar = false;
					
				}
				else if (this->inRocket) {
					EntityManager::DisableComponent(entityIDs[ROCKET_CONNECTION], CONTROLS);
					EntityManager::DisableComponent(entityIDs[GUN_CONNECTION], CONTROLS);
					EntityManager::DisableComponent(entityIDs[GUN_CONNECTION], PHYSICS);
					EntityManager::EnableComponent(this->GetEntityID(), PHYSICS);
					EntityManager::EnableComponent(this->GetEntityID(), GRAPHICS);

					ComponentMessage::Transform trans;
					ComponentMessage comp_msg(PHYSICS, ComponentMessage::GET_TRANSFORM, &trans);
					EntityManager::SendMessage(entityIDs[ROCKET_CONNECTION], comp_msg);

					b2Body * tempBody;
					ComponentMessage comp_msg2(PHYSICS, ComponentMessage::GET_BODY, &tempBody);
					EntityManager::SendMessage(this->GetEntityID(), comp_msg2);
					tempBody->SetActive(true);

					trans.angle = 0; // we don't want to rotate the character
					comp_msg.funcID = ComponentMessage::SET_TRANSFORM;
					EntityManager::SendMessage(this->GetEntityID(), comp_msg);

					this->inRocket = false;
				}
				this->occupied = false;
				
			}
			else {
				if (this->touchingBalloon) {

					b2Body * tempBody;
					ComponentMessage comp_msg(PHYSICS, ComponentMessage::GET_BODY, &tempBody);

					EntityManager::SendMessage(this->entityIDs[BALLOON_CONNECTION], comp_msg);
					tempBody->SetGravityScale(-10);

					EntityManager::SendMessage(this->entityIDs[SEGMENT_CONNECTION], comp_msg);
					jointDef.bodyA = tempBody;

					EntityManager::SendMessage(this->GetEntityID(), comp_msg); // TODO Needs to be double checked
					jointDef.bodyB = tempBody;

					jointDef.collideConnected = false;
					jointDef.localAnchorA.Set(0, .25);
					jointDef.localAnchorB.Set(0, -.5);
					this->m_joint = (b2RevoluteJoint*)Globals::world.CreateJoint(&jointDef);

					this->inBalloon = true;
				}
				else if (this->touchingCar) {
					EntityManager::EnableComponent(entityIDs[CAR_CONNECTION], CONTROLS);
					EntityManager::DisableComponent(this->GetEntityID(),PHYSICS);
					EntityManager::DisableComponent(this->GetEntityID(), GRAPHICS);

					b2Body * tempBody;
					ComponentMessage comp_msg(PHYSICS, ComponentMessage::GET_BODY, &tempBody);
					EntityManager::SendMessage(this->GetEntityID(), comp_msg);
					tempBody->SetActive(false);

					this->inCar = true;
				}
				else if (this->touchingRocket) {

					EntityManager::EnableComponent(entityIDs[ROCKET_CONNECTION], CONTROLS);
					EntityManager::EnableComponent(entityIDs[GUN_CONNECTION], CONTROLS);
					EntityManager::EnableComponent(entityIDs[GUN_CONNECTION], PHYSICS);
					EntityManager::DisableComponent(this->GetEntityID(), PHYSICS);
					EntityManager::DisableComponent(this->GetEntityID(), GRAPHICS);
					b2Body * tempBody;
					ComponentMessage comp_msg(PHYSICS, ComponentMessage::GET_BODY, &tempBody);
					EntityManager::SendMessage(this->GetEntityID(), comp_msg);
					tempBody->SetActive(false);
					this->inRocket = true;
				}

				this->occupied = true;
			}

			break;
		}

		}
	}


};