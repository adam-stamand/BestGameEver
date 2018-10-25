#include "SFMLManager.h"
#include <assert.h>
#include "Types.h"


std::map<std::string, sf::RenderWindow*> SFMLManager::windowMap = { {"init", new sf::RenderWindow(sf::VideoMode(800, 600), "Best Game Ever", sf::Style::Default)} };

std::vector<sf::Event> SFMLManager::events_occured;
sf::Music SFMLManager::music;

void SFMLManager::ClearEvents(void) {
  events_occured.clear();
}


sf::Event *SFMLManager::FindEvent(sf::Event::EventType evnt) {
  for (int i = 0; i < events_occured.size(); i++) {
    if (events_occured.at(i).type == evnt) {
      return &events_occured.at(i);
    }
  }
  return NULL;
}


void SFMLManager::GetEvents(sf::Window * window) {
  sf::Event evnt;
  while (window->pollEvent(evnt)) {
    events_occured.push_back(evnt);
  }
}




void SFMLManager::RemoveWindow(std::string name) {
  auto iter = windowMap.erase(name);
}


int SFMLManager::GetWindow(std::string name, sf::RenderWindow *&window) {
  auto iter = windowMap.find(name);
  if (iter == windowMap.end()) {
    assert(0);
    return -1;
  }
  window = iter->second;
  return 0;
}



void SFMLManager::AddWindow(std::string name, sf::RenderWindow * window) {
  windowMap.insert(std::pair<std::string, sf::RenderWindow*>(name, window));
}

void SFMLManager::DisplayWindows() {
  for (auto iter = windowMap.begin(); iter != windowMap.end(); iter++) {
    iter->second->display();
  }
}



void SFMLManager::ClearWindows() {
  for (auto iter = windowMap.begin(); iter != windowMap.end(); iter++) {
    iter->second->clear();
  }
}


std::map<std::string, sf::RenderWindow*>::const_iterator SFMLManager::windows_begin() {
  return SFMLManager::windowMap.begin();
}

std::map<std::string, sf::RenderWindow*>::const_iterator SFMLManager::windows_end() {
  return SFMLManager::windowMap.end(); 
}


void SFMLManager::PlayBackgroundMusic(std::string name, bool loop) {
  SFMLManager::music.openFromFile(name);
  SFMLManager::music.setLoop(loop);
  SFMLManager::music.play();
}
