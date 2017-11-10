#pragma once
#include "Entity/EntityBase.h"

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void DetectCollision(EntityBase *entity1, EntityBase *entity2);
	void Register(EntityBase *entity);
	void HandleCollisions();

private:
	std::vector<EntityBase *> entities;

};

