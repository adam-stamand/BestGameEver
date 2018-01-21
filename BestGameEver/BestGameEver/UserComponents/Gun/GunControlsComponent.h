#pragma once

#include "BaseComponents/SFMLControls/SFMLControlsComponent.h"
#include "Manager/SFMLManager/SFMLManager.h"
#include "BaseComponents/Message.h"

class GunControlsComponent : public SFMLControlsComponent<GunControlsComponent>
{
public:
	GunControlsComponent(std::string name);
	~GunControlsComponent() {};

	void GunControlsComponent::FireGun(sf::Event &evnt);

  void Update() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
    TransformMessage trans;
    PublishMessage(trans, "GetTransform");

    float angle = std::atan2((mousePos.y - trans.translation.y), (mousePos.x - trans.translation.x)) + 1.571;
    trans.rotation = RAD_2_DEGREES(angle);
    PublishMessage(trans, "SetTransform");
  }

  sf::RenderWindow * window;

};

