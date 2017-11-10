#include "Entity/GraphicsComponent.h"


sf::Font GraphicsComponent::font;


GraphicsComponent::GraphicsComponent(char ch) {
 /*
 text.setString(ch);
 text.setCharacterSize(50);
 text.setPosition(40, 40);
 GraphicsComponent::font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
 text.setFont(GraphicsComponent::font);
 */


	texture.loadFromFile("Images/rocket_ship.jpg");
	sprite.setTexture(texture);
 //this->sprite.setColor(sf::Color(0, 55, 05, 128));
 this->sprite.setPosition(200.f, 100.f);
 this->sprite.setRotation(30.f);

 //sf::FloatRect rect = sprite.getGlobalBounds();
 //this->sprite.setOrigin(, 0);
 this->sprite.setScale(.25f, 0.25f);	
 this->ID = GRAPHICS;
}
