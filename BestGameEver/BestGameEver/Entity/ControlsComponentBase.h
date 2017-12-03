#pragma once

#include "Entity/ComponentBase.h"
#include "Entity/EntityInterface.h"
#include "Entity/Message.h"
#include "Level/EventHandler.h"
#include <assert.h>


// Maybe clean up??

template <class T>
class ControlsComponentBase : public ComponentBase
{
public:
	template <class T>
	ControlsComponentBase(T *child) : ComponentBase(CONTROLS) { this->child = child; }

	~ControlsComponentBase() {};
	void Update(EntityInterface &entity);
protected:

	typedef T ControlsComponent_t;
	typedef void(T::*KeyPress_Func_P)(EntityInterface &entity);
	typedef void(T::*Event_Func_P)(sf::Event &evnt, EntityInterface &entity);

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


	void CheckEventActions(T &object, EntityInterface &entity);
	void CheckKeyPressActions(T &object, EntityInterface &entity);

	void RegisterAction(ControlKeys key_vec, KeyPress_Funcs funcs);
	void RegisterAction(sf::Event::EventType evnt, Event_Funcs funcs);

	KeyPressAction key_action;
	EventAction evnt_action;

private:
	T *child;
	std::vector<EventAction> event_action_map;
	std::vector<KeyPressAction> key_action_map;
};





template <class T>
void ControlsComponentBase<T>::Update(EntityInterface &entity) {
	this->CheckKeyPressActions(*child, entity);
	this->CheckEventActions(*child,entity);
}


template <class T>
void ControlsComponentBase<T>::CheckKeyPressActions(T &object, EntityInterface &entity) {

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
				(object.*(key_action_map.at(i).funcs.at(l)))(entity);
			}
		}
	}
}


template <class T>
void ControlsComponentBase<T>::CheckEventActions(T &object, EntityInterface &entity) {

	for (long int i = 0; i < event_action_map.size(); i++) {
		sf::Event *evnt_p;
		evnt_p = EventHandler::FindEvent(event_action_map.at(i).evnt);
		if (evnt_p != NULL) {
			for (int l = 0; l < event_action_map.at(i).funcs.size(); l++) {
				(object.*(event_action_map.at(i).funcs.at(l)))(*evnt_p, entity);
			}
		}
	}
}


template <class T>
void ControlsComponentBase<T>::RegisterAction(sf::Event::EventType evnt, Event_Funcs funcs) {
	assert(funcs.size() > 0);
	evnt_action.evnt = evnt;
	evnt_action.funcs.insert(evnt_action.funcs.end(), funcs.begin(), funcs.end());
	event_action_map.push_back(evnt_action);
	evnt_action.funcs.clear();
}


template <class T>
void ControlsComponentBase<T>::RegisterAction(ControlKeys key_vec, KeyPress_Funcs funcs) {

	assert(key_vec.size() > 0 && funcs.size() > 0);
	key_action.keys_pressed.insert(key_action.keys_pressed.end(), key_vec.begin(), key_vec.end());
	key_action.funcs.insert(key_action.funcs.end(), funcs.begin(), funcs.end());
	key_action_map.push_back(key_action);
	key_action.keys_pressed.clear();
	key_action.funcs.clear();
}