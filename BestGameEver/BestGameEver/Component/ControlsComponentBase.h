#pragma once

#include "Component/ComponentBase.h"
#include "Manager/EventManager.h"
#include <assert.h>

// Could probably still cleanup

template <class T>
class ControlsComponentBase : public ComponentBase
{
public:
	template <class T>
	ControlsComponentBase(T *child) : ComponentBase(CONTROLS) { this->child = child; }
	~ControlsComponentBase() {};

	
	void Update() {
		this->CheckKeyPressActions(*child);
		this->CheckEventActions(*child);
		ComponentUpdate();
	};

	void MessageHandler(ComponentMessage &msg) {ComponentMessageHandler(msg);};
	
	virtual void ComponentUpdate() {};
	virtual void ComponentMessageHandler(ComponentMessage &msg) {};
	


private:
	typedef T ControlsComponent_t;
	typedef void(T::*KeyPress_Func_P)();
	typedef void(T::*Event_Func_P)(sf::Event &evnt);

	typedef std::vector<sf::Keyboard::Key> ControlKeys;
	typedef std::vector<KeyPress_Func_P> KeyPress_Funcs;
	typedef std::vector<Event_Func_P> Event_Funcs;

	struct EventAction {
		sf::Event::EventType evnt;
		Event_Funcs funcs;
	};

	struct KeyPressAction {
		ControlKeys keys_pressed;
		KeyPress_Funcs funcs;
	};


	void CheckEventActions(T &object);
	void CheckKeyPressActions(T &object);

	T *child;
	std::vector<EventAction> event_action_map;
	std::vector<KeyPressAction> key_action_map;

protected:

	void RegisterAction(ControlKeys key_vec, KeyPress_Funcs funcs);
	void RegisterAction(sf::Event::EventType evnt, Event_Funcs funcs);


};


template <class T>
void ControlsComponentBase<T>::CheckKeyPressActions(T &object) {

	for (long int i = 0; i < key_action_map.size(); i++) {
		bool skip_flag = false;

		for (int j = 0; j < key_action_map.at(i).keys_pressed.size(); j++) {

			if (!sf::Keyboard::isKeyPressed(key_action_map.at(i).keys_pressed.at(j))) {
				skip_flag = true;
				break;
			}
		}

		if (!skip_flag) {
			for (int l = 0; l < key_action_map.at(i).funcs.size(); l++) {
				(object.*(key_action_map.at(i).funcs.at(l)))();
			}
		}
	}
}


template <class T>
void ControlsComponentBase<T>::CheckEventActions(T &object) {

	for (long int i = 0; i < event_action_map.size(); i++) {
		sf::Event *evnt_p;
		evnt_p = EventManager::FindEvent(event_action_map.at(i).evnt);
		if (evnt_p != NULL) {
			for (int l = 0; l < event_action_map.at(i).funcs.size(); l++) {
				(object.*(event_action_map.at(i).funcs.at(l)))(*evnt_p);
			}
		}
	}
}


template <class T>
void ControlsComponentBase<T>::RegisterAction(sf::Event::EventType evnt, Event_Funcs funcs) {
	assert(funcs.size() > 0);
	EventAction evnt_action;
	evnt_action.evnt = evnt;
	evnt_action.funcs = funcs;
	//evnt_action.funcs.insert(evnt_action.funcs.end(), funcs.begin(), funcs.end()); // can proabbly just copy vector instead of insert
	event_action_map.push_back(evnt_action);
}


template <class T>
void ControlsComponentBase<T>::RegisterAction(ControlKeys key_vec, KeyPress_Funcs funcs) {
	assert(key_vec.size() > 0 && funcs.size() > 0);
	KeyPressAction key_action;
	key_action.keys_pressed = key_vec;
	key_action.funcs = funcs;
	//key_action.keys_pressed.insert(key_action.keys_pressed.end(), key_vec.begin(), key_vec.end());
	//key_action.funcs.insert(key_action.funcs.end(), funcs.begin(), funcs.end());
	key_action_map.push_back(key_action);
}