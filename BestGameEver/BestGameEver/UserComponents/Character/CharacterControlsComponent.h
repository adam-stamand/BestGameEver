#pragma once

#include "BaseComponents/SFMLControls/SFMLControlsComponent.h"

class CharacterControlsComponent : public SFMLControlsComponent<CharacterControlsComponent>
{
public:
	//RateLimiter rateLimiter;
	CharacterControlsComponent(std::string name);
	~CharacterControlsComponent() {};

private:
	void Enter();
	void Grenade();
	void MoveLeft();
	void MoveRight();
};

