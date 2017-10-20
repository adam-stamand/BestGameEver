#include <SFML/Graphics.hpp>


int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Hello SFML1", sf::Style::Default);
	sf::Font font;
	font.loadFromFile("C:/Windows/Fonts/Arial.ttf");

	sf::Text text;
	text.setFont(font);
	text.setPosition(200, 200);
	text.setString("Hello Garrett");

	while (window.isOpen())
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			if ((evnt.type == sf::Event::KeyPressed) && (evnt.key.code == sf::Keyboard::Escape))
				printf("asdf");

			                                                                                                                                                                                  
		}
		window.clear();
		window.draw(text);
		window.display();
	}

	return 0;
}