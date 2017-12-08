#include "Manager/EventManager.h"


std::vector<sf::Event> EventManager::events_occured;


void EventManager::ClearEvents(void) {
	events_occured.clear();
}


sf::Event *EventManager::FindEvent(sf::Event::EventType evnt) {
	for (int i = 0; i < events_occured.size(); i++) {
		if (events_occured.at(i).type == evnt) {
			return &events_occured.at(i);
		}
	}
	return NULL;
}


void EventManager::GetEvents(sf::Window &window) {
	sf::Event evnt;
	while (window.pollEvent(evnt)) {
		events_occured.push_back(evnt);
	}
}


