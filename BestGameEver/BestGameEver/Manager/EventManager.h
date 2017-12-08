#pragma once

#include <SFML/Graphics.hpp>


class EventManager
{
public:

	static void EventManager::GetEvents(sf::Window &window);
	static void EventManager::ClearEvents(void);
	static sf::Event *EventManager::FindEvent(sf::Event::EventType evnt);

private:
	static std::vector<sf::Event> EventManager::events_occured;
};



