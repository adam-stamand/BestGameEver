#pragma once
#include <vector>
#include <SFML/Graphics.hpp>


class EventHandler {

public:

	
	static void EventHandler::GetEvents(sf::Window &window);
	static void EventHandler::ClearEvents(void);
	static sf::Event *EventHandler::FindEvent(sf::Event::EventType evnt);
private:

	static std::vector<sf::Event> EventHandler::events_occured;


};



