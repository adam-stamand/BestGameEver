#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{

	RenderWindow window(VideoMode(800, 600), "FFFFF", Style::Default);

	Font font;
	font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
	sf::Clock deltaClock;
	Text text;
	text.setFont(font);

	char mander = '>';
	//mander = getchar();

	uint32_t x=200, y=200;

	while (window.isOpen())
	{

		sf::Time deltaTime = deltaClock.restart();

		Event evnt;
		text.setPosition(x, y);
		text.setString(mander);
		window.clear();
		window.draw(text);
		window.display();
		
	//	printf("%d", deltaTime.asMilliseconds());
		while (window.pollEvent(evnt))
		{

			switch (evnt.type) 
			{
			
			case Event::KeyPressed:

				if (evnt.key.code == sf::Keyboard::Escape) {
					window.close();
				}
				else if (evnt.key.code == sf::Keyboard::A) {
					x -= 10;
					mander = '<';

				}
				else if (evnt.key.code == sf::Keyboard::D) {
					x += 10;
					mander = '>';
				}
				else if (evnt.key.code == sf::Keyboard::W) {
					y -= 10;
					mander = '^';
				}
				else if (evnt.key.code == sf::Keyboard::S) {
					y += 10;
					mander = 'v';
				}
				break;
			}
		}
	}

	return 0;
}