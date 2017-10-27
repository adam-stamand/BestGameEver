#include "EventHandler.h"


std::vector<sf::Event> EventHandler::events_occured;





void EventHandler::ClearEvents(void) {
	events_occured.clear();
}

sf::Event *EventHandler::FindEvent(sf::Event::EventType evnt) {
	for (int i = 0; i < events_occured.size(); i++) {
		if (events_occured.at(i).type == evnt) {
			return &events_occured.at(i);
		}
	}
	return NULL;
}


void EventHandler::GetEvents(sf::Window &window) {
	sf::Event evnt;
	while (window.pollEvent(evnt)) {
		events_occured.push_back(evnt);
	}
}


