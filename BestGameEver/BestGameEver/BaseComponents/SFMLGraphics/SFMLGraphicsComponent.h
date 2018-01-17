#pragma once
#include "FWInterface/Component.h"
#include "Factory/SFMLFactory/SFMLFactory.h"



class SFMLGraphicsComponent : public Component
{
public:

  
  SFMLGraphicsComponent(std::string name, std::vector<Sprite*> sprites, std::string windowName = "init");
	~SFMLGraphicsComponent() {};

	void Update();

protected:
  
	void DrawSprite(sf::Sprite &sprite, b2Vec2 center, float  angle);
	
private:
  sf::RenderWindow *window;
  std::vector<Sprite*> sprites;
  void GetLocalTransformation(b2Vec2 &translation, float &rotation, Sprite &sprite);
	void ApplyRotation(b2Vec2 &localPoint, float &localRotation, float &rotation);
  void ApplyTranslation(flVec2 &localTranslation, flVec2 &worldTranslation);

};
