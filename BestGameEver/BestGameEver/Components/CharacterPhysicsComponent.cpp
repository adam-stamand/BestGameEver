#include "CharacterPhysicsComponent.h"





CharacterPhysicsComponent::~CharacterPhysicsComponent()
{
}

float32 CharacterPhysicsComponent::CharacterRayCast::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) {
	this->fixture = fixture;
	this->point = point;
	this->normal = normal;
	return fraction;
}
