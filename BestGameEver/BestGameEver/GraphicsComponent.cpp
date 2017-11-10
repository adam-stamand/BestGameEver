#include "Entity/GraphicsComponent.h"


sf::Font GraphicsComponent::font;


GraphicsComponent::GraphicsComponent(char ch) {
 
 text.setString(ch);
 text.setCharacterSize(50);
 text.setPosition(40, 40);
 GraphicsComponent::font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
 text.setFont(GraphicsComponent::font);
 
	sf::Image image;
	image.create(50, 50, sf::Color::Red);
	sf::Texture texture;
	texture.loadFromImage(image);
 //this->sprite.setColor(sf::Color(0, 55, 05, 128));
 //this->sprite.setPosition(200.f, 100.f);
 //this->sprite.setRotation(30.f);
 //this->sprite.setOrigin(0, 0);
 //this->sprite.setScale(2.f, 0.5f);	
 this->ID = GRAPHICS;
}
