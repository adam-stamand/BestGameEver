#pragma once
#include "Entity/EntityBase.h"
#include "Level/EventHandler.h"

template <class T>
class ControlsBase
{
public:
	ControlsBase();
	~ControlsBase();


protected:

	typedef std::vector<sf::Keyboard::Key> ControlKeys;
	typedef void(T::*KeyPress_Func_P)(EntityBase &entity);
	typedef void(T::*Event_Func_P)(sf::Event &evnt, EntityBase &entity);

	struct EventAction {
		sf::Event::EventType evnt_type;
		Event_Func_P func_ptr;
	};

	struct KeyPressAction {
		ControlKeys keys_pressed;
		KeyPress_Func_P func_ptr;
	};


	void CheckEventActions(T &object, EntityBase &entity);
	void CheckKeyPressActions(T &object, EntityBase &entity);
	void RegisterEventAction(EventAction &action);
	void RegisterKeyPressAction(KeyPressAction &action);



private:

	std::vector<EventAction> event_action_map;
	std::vector<KeyPressAction> key_action_map;

};


template <class T>
ControlsBase<T>::ControlsBase()
{
}


template <class T>
ControlsBase<T>::~ControlsBase()
{
}


template <class T>
void ControlsBase<T>::CheckKeyPressActions(T &object, EntityBase &entity) {

	for (long int i = 0; i < key_action_map.size(); i++) {
		bool skip_flag = false;

		for (int j = 0; j < key_action_map.at(i).keys_pressed.size(); j++) {

			if (!sf::Keyboard::isKeyPressed(key_action_map.at(i).keys_pressed.at(j))) {
				skip_flag = true;
				break;
			}
		}

		if (!skip_flag) {
			(object.*(key_action_map.at(i).func_ptr))(entity);
		}
	}
}


template <class T>
void ControlsBase<T>::CheckEventActions(T &object, EntityBase &entity) {

	for (long int i = 0; i < event_action_map.size(); i++) {
		sf::Event *evnt_p;
		evnt_p = EventHandler::FindEvent(event_action_map.at(i).evnt_type);
		if (evnt_p != NULL) {
			(object.*(event_action_map.at(i).func_ptr))(*evnt_p, entity);
		}

	}
}

template <class T>
void ControlsBase<T>::RegisterEventAction(EventAction &action) {
	event_action_map.push_back(action);
}

template <class T>
void ControlsBase<T>::RegisterKeyPressAction(KeyPressAction &action) {
	key_action_map.push_back(action);
	action.keys_pressed.clear();
}
