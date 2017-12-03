#include "GunPhysicsComponent.h"


float32 GunPhysicsComponent::GunRayCast::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) {
	this->fixture = fixture;
	this->point = point;
	this->normal = normal;
	return fraction;
}

