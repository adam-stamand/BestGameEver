#pragma once

#include <math.h>
#include <string.h>

#include "Component/ComponentBase.h"
#include "Factory/Item.h"
#include "Globals/Globals.h"

class GraphicsComponentBase : public ComponentBase
{
public:
	GraphicsComponentBase(sf::RenderWindow *window, Item * item);
	~GraphicsComponentBase() {};

	void Update();
	void MessageHandler(ComponentMessage &msg);
	virtual void ComponentUpdate() {};
	virtual void ComponentMessageHandler(ComponentMessage &msg) {};

protected:
	void DrawSprite(sf::Sprite &sprite, b2Vec2 center, float  angle);
	sf::RenderWindow *window;
	Item * item;
private:
	void GraphicsComponentBase::GetWorldTransformation(b2Vec2 &translation, float &rotation, Item &item);
	void GraphicsComponentBase::GetLocalTransformation(b2Vec2 &translation, float &rotation, Part &part);
	void GraphicsComponentBase::Transform2d(b2Vec2 &localPoint, float &localRotation, float &rotation);
};
