#include "CollisionManager.h"



CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}


void CollisionManager::HandleCollisions() {
	for (int i = 0; i < this->entities.size(); i++) {
		for (int j = i + 1; j < this->entities.size(); j++) {
			this->DetectCollision(entities.at(i), entities.at(j));
		}
	}

}

void CollisionManager::DetectCollision(EntityBase *entity1, EntityBase *entity2) {
	if (entity1->x_pos);
}

void CollisionManager::Register(EntityBase *entity) {
	this->entities.push_back(entity);
}