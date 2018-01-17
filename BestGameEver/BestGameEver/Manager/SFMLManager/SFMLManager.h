#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class SFMLManager
{
public:

 static std::map<std::string, sf::RenderWindow*> windowMap;

  static void DisplayWindows();
  static void ClearWindows();

  static sf::RenderWindow * RemoveWindow(std::string name);
  static void AddWindow(std::string name, sf::RenderWindow * window);
  static int GetWindow(std::string name, sf::RenderWindow * &window);
  static std::map<std::string, sf::RenderWindow*>::const_iterator windows_begin();
  static std::map<std::string, sf::RenderWindow*>::const_iterator windows_end();

  static void GetEvents(sf::Window * window);
  static void ClearEvents(void);
  static sf::Event * FindEvent(sf::Event::EventType evnt);

  static void PlayBackgroundMusic(std::string name, bool loop = true);
  

private:
  static sf::Music music;
  static std::vector<sf::Event> events_occured;

};

