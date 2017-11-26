#pragma once

#include "Entity/ComponentBase.h"
#include "Entity/Entity.h"
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

protected:

	typedef T ControlsComponent_t;
	typedef void(T::*KeyPress_Func_P)(Entity &entity);
	typedef void(T::*Event_Func_P)(sf::Event &evnt, Entity &entity);

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

	void Update(EntityBase &entity);
	void CheckEventActions(T &object, Entity &entity);
	void CheckKeyPressActions(T &object, Entity &entity);

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
// TODO Look into static cast and make sure that's what we want
void ControlsComponentBase<T>::Update(EntityBase &entity) {
	this->CheckKeyPressActions(*child, static_cast<Entity&>(entity));
	this->CheckEventActions(*child, static_cast<Entity&>(entity));
}


template <class T>
void ControlsComponentBase<T>::CheckKeyPressActions(T &object, Entity &entity) {

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
void ControlsComponentBase<T>::CheckEventActions(T &object, Entity &entity) {

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