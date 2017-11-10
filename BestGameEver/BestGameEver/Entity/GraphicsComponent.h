#pragma once
#include "Entity/Component.h"

class GraphicsComponent : public Component
{

public:
	GraphicsComponent(std::string path);
	~GraphicsComponent() {};

	virtual void Update(EntityBase &entity, sf::RenderWindow &window);
	void setTexture(std::string path);
private:
	sf::Sprite sprite;
	sf::Texture texture;


};

