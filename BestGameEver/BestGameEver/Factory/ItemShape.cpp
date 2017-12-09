#include "ItemShape.h"
#include "Globals/Globals.h"



b2Shape * CircleItem::GetShape(b2Vec2 size, b2Vec2 center, float angle) {

	// ignore angle, rotating a circle doesn't matter, unless ?...
	this->radius = (this->radius * size.x) / 2;
	this->point.x = (this->point.x * size.x) + center.x;
	this->point.y = (this->point.y * size.y) + center.y;
	b2CircleShape * circleShape = new b2CircleShape;

	circleShape->m_p.Set(this->point.x, this->point.y);
	circleShape->m_radius = this->radius;
	return circleShape;
}


b2Shape *  PolyItem::GetShape(b2Vec2 size, b2Vec2 center, float angle) {


	for (int j = 0; j < this->coords.size(); j++) {

		float xPos = (this->coords.at(j).x * size.x) - size.x / 2;
		float yPos = (this->coords.at(j).y * size.y) - size.y / 2;

		// Move 2D rotation to utilities or soemthing
		this->coords.at(j).x = cos(angle) * xPos - sin(angle) * yPos;
		this->coords.at(j).y = sin(angle) * xPos + cos(angle) * yPos;

		this->coords.at(j).x +=center.x;
		this->coords.at(j).y +=center.y;
	}




	b2PolygonShape * polyShape = new b2PolygonShape;
	polyShape->Set((b2Vec2*)(&this->coords.at(0)), this->coords.size());
	return polyShape;


}


b2Shape * ChainItem::GetShape(b2Vec2 size, b2Vec2 center, float angle) {



	for (int j = 0; j < this->coords.size(); j++) {

		float xPos = (this->coords.at(j).x * size.x) - size.x / 2;
		float yPos = (this->coords.at(j).y * size.y) - size.y / 2;

		// Move 2D rotation to utilities or soemthing
		this->coords.at(j).x = cos(angle) * xPos - sin(angle) * yPos;
		this->coords.at(j).y = sin(angle) * xPos + cos(angle) * yPos;

		this->coords.at(j).x += center.x;
		this->coords.at(j).y += center.y;
	}



	//TODO: make fleixble enough to make loop or chain
	b2ChainShape * chainShape = new b2ChainShape;
	chainShape->CreateLoop((b2Vec2*)(&this->coords.at(0)), this->coords.size());
	return chainShape;


}