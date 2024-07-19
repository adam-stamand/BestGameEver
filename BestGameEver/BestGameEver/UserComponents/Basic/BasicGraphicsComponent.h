#pragma once

#include "BaseComponents/SFMLGraphics/SFMLGraphicsComponent.h"


class BasicGraphicsComponent : public SFMLGraphicsComponent
{
public:
	BasicGraphicsComponent(std::string name, std::vector<Sprite*> sprites, std::string windowName = "init") : SFMLGraphicsComponent(name, sprites, windowName) {};
	~BasicGraphicsComponent() {};
};

