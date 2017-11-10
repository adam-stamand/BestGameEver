#include "Entity/GraphicsComponent.h"



GraphicsComponent::GraphicsComponent(std::string path) {

	setTexture(path);
	this->ID = GRAPHICS;
}

void GraphicsComponent::Update(EntityBase & entity, sf::RenderWindow & window)
{
		this->sprite.setPosition(entity.x_pos, entity.y_pos);
		this->sprite.setRotation(entity.rotation);
		window.draw(this->sprite);	

}

void GraphicsComponent::setTexture(std::string path)
{
	texture.loadFromFile(path);
	sprite.setTexture(texture);
}



