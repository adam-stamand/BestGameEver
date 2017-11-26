#include "ItemShape.h"
#include "Globals/Globals.h"



b2Shape * CircleItem::GetShape(sf::Sprite &sprite) {


	float xSize = sprite.getTexture()->getSize().x;
	float ySize = sprite.getTexture()->getSize().y;

	float xScale = sprite.getScale().x;
	float yScale = sprite.getScale().y;

	this->radius = SF_2_BOX(this->radius * xScale * xSize);
	this->point.x = SF_2_BOX(this->point.x * xScale * xSize) - SF_2_BOX(xScale *xSize / 2);
	this->point.y = SF_2_BOX(this->point.y * yScale * ySize) - SF_2_BOX(yScale *ySize / 2);

	b2CircleShape * circleShape = new b2CircleShape;
	circleShape->m_p.Set(this->point.x, this->point.y);
	circleShape->m_radius = this->radius;
	return circleShape;
}


b2Shape *  PolyItem::GetShape(sf::Sprite &sprite) {

	float xSize = sprite.getTexture()->getSize().x;
	float ySize = sprite.getTexture()->getSize().y;

	float xScale = sprite.getScale().x;
	float yScale = sprite.getScale().y;


	for (int j = 0; j < this->coords.size(); j++) {
		this->coords.at(j).x = (SF_2_BOX(this->coords.at(j).x * xScale * xSize * 1)) - SF_2_BOX((xScale *xSize / 2 * 1));
		this->coords.at(j).y = (SF_2_BOX(this->coords.at(j).y * yScale * ySize * 1)) - SF_2_BOX((yScale *ySize / 2 * 1));
	}

	b2PolygonShape * polyShape = new b2PolygonShape;
	polyShape->Set((b2Vec2*)(&this->coords.at(0)), this->coords.size());
	//polyShape->Set(array, 4);
	return polyShape;


}
