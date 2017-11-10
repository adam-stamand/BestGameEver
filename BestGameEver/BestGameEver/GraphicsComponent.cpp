#include "Entity/GraphicsComponent.h"


sf::Font GraphicsComponent::font;


GraphicsComponent::GraphicsComponent(char ch) {
 text.setString(ch);
 text.setCharacterSize(50);
 text.setPosition(40, 40);
 GraphicsComponent::font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
 text.setFont(GraphicsComponent::font);
 this->ID = GRAPHICS;
}
