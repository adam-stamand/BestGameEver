#pragma once
#include <SFML/Graphics.hpp>
#include "EventHandler.h"

#define MAX_CONTROLS	50
#define MAX_KEYS		5

template <class T>
class Controllable
{

public:
	Controllable();
	~Controllable();

	typedef void(T::*KeyPress_Func_P)();
	typedef void(T::*Event_Func_P)(sf::Event &evnt);

	struct EventAction {
		sf::Event::EventType evnt_type;
		Event_Func_P func_ptr;
		long int ID;
	};

	struct KeyPressAction {
		std::vector<sf::Keyboard::Key> keys_pressed;
		KeyPress_Func_P func_ptr;
		long int ID;
	};

	void Controllable::CheckEventActions(T &object);
	void Controllable::CheckKeyPressActions(T &object);
	void Controllable::DeregisterKeyPressAction(long int ID);
	void Controllable::DeregisterEventAction(long int ID);
	void Controllable::RegisterEventAction(EventAction action);
	void Controllable::RegisterKeyPressAction(KeyPressAction action);


private:
	std::vector<EventAction> event_action_map;
	std::vector<KeyPressAction> key_action_map;
};



template <class T>
void Controllable<T>::CheckKeyPressActions(T &object) {

	for (long int i = 0; i < key_action_map.size(); i++) {
		bool skip_flag = false;

		for (int j = 0; j < key_action_map.at(i).keys_pressed.size(); j++) {

			if (!sf::Keyboard::isKeyPressed(key_action_map.at(i).keys_pressed.at(j))) {
				skip_flag = true;
				break;
			}
		}

		if (!skip_flag) {
			(object.*(key_action_map.at(i).func_ptr))();
		}
	}
}


template <class T>
void Controllable<T>::CheckEventActions(T &object) {
	
	for (long int i = 0; i < event_action_map.size(); i++) {
		sf::Event *evnt_p;
		evnt_p = EventHandler::FindEvent(event_action_map.at(i).evnt_type);
		if (evnt_p != NULL) {
			(object.*(event_action_map.at(i).func_ptr))(*evnt_p);
		}

	}
}

template <class T>
void Controllable<T>::DeregisterKeyPressAction(long int ID) {
	for (long int i = 0; i < key_action_map.size(); i++) {
		if (key_action_map.at(i).ID == ID) {
			key_action_map.erase(key_action_map.begin() + i);
			return;
		}
	}
}


template <class T>
void Controllable<T>::DeregisterEventAction(long int ID) {
	for (long int i = 0; i < event_action_map.size(); i++) {
		if (event_action_map.at(i).ID == ID) {
			event_action_map.erase(event_action_map.begin() + i);
			return;
		}
	}
}

template <class T>
void Controllable<T>::RegisterEventAction(EventAction action) {
	event_action_map.push_back(action);
	printf("%d\n", event_action_map.size());
}

template <class T>
void Controllable<T>::RegisterKeyPressAction(KeyPressAction action) {
	key_action_map.push_back(action);
}

template <class T>
Controllable<T>::Controllable()
{
}

template <class T>
Controllable<T>::~Controllable()
{
}
