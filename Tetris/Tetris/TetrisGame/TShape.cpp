#include "TShape.h"


#include <iostream>
#include <random>

#include "GTetris.h"
#include "../GUtils.h"
using namespace TetrisShapes;

TShape::TShape(int iType, const sf::Vector2f& iCenter) {
	parts = 4;
	type = iType;
	center = iCenter;
	m_cachePos.resize(parts+1);
	init();
	switch (iType)
		{
		case TetrisShapes::ShapeType::I:
			{
				initI();
				break;
			}
		case TetrisShapes::ShapeType::O:
			{
				initO();
				break;
			}
		case TetrisShapes::ShapeType::T:
			{
				initT();
				break;
			}
		case TetrisShapes::ShapeType::Z:
			{
				initZ();
				break;
			}
		case TetrisShapes::ShapeType::S:
			{
				initS();
				break;
			}
		case ShapeType::J:
			{
				initJ();
				break;
			}
		case ShapeType::L:
		{
			initL();
			break;
		}
			default:
			{
				break;
			}
		}
}
void TShape::rotate(bool clockWise)
{
	if (type == ShapeType::O)
		return;
	int dir = clockWise ? 1 : -1;
	for (int i = 0; i < shapeParts; i++) {
		sf::Vector2f pos = m_rects[i].getPosition();
		float x = pos.x + rectSize / 2 - center.x;
		float y = pos.y + rectSize / 2 - center.y;
		pos.x = center.x - y*dir - rectSize / 2;
		pos.y = center.y + x*dir - rectSize / 2;
		m_rects[i].setPosition(pos);
	}
	
}

void TShape::processEvent(float iTime, int iEventIdx)
{
	eventIdx = iEventIdx;
	for (int i = 0; i < parts; i++) {
		m_cachePos[i] = m_rects[i].getPosition();
	}
	m_cachePos.back() = center;
	if (m_events[iEventIdx]->type == GEvent::EventType::RotationEnd && rotated) {
		rotated = false;
	}
	if (m_events[iEventIdx]->type == GEvent::EventType::RotationStart && !rotated) {
		rotated = true;
		rotate();
	}
	if (m_events[iEventIdx]->type == GEvent::EventType::Motion) {
		GEventMotion* event = (GEventMotion*)(m_events[iEventIdx]);
		const sf::Vector2f& motion = event->getMotion() * iTime;
		moveShape(motion);
	}
}
void TShape::moveShape(const sf::Vector2f& iMotion)
{
	for (int rectIdx = 0; rectIdx < TetrisShapes::shapeParts; rectIdx++) {
		m_rects[rectIdx].move(iMotion);
	}
	center.x += iMotion.x;
	center.y += iMotion.y;
}

RectInterInfo TShape::intersectShape(const TShape* ipOtherShape, sf::FloatRect& oIntersection) const
{
	sf::FloatRect inter;
	for (int i = 0; i < parts; i++) {
		for (int j = 0; j < parts; j++) {
			if (m_rects[i].getGlobalBounds().intersects(ipOtherShape->m_rects[j].getGlobalBounds(), oIntersection)) {
				return RectInterInfo(m_rects[i].getPosition(), ipOtherShape->m_rects[j].getPosition());
			}
		}
	}
	return RectInterInfo();
}


void TShape::revertLastEvent() {
	if (m_events[eventIdx]->type == GEvent::EventType::RotationStart){
		rotated = false;
	}
	for (int i = 0; i < parts; i++) {
		m_rects[i].setPosition(m_cachePos[i]);
	}
	center = m_cachePos[4];
} 
void TShape::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < TetrisShapes::shapeParts; i ++) {
		target.draw(m_rects[i]);
	}
	if (debug)
	{
		sf::CircleShape centerShape(1);
		centerShape.setPosition(center);
		centerShape.setFillColor(sf::Color::Red);
		target.draw(centerShape);
		sf::FloatRect ext = getExtents();
		sf::RectangleShape rect({ ext.width,ext.height });
		rect.setPosition(ext.left, ext.top);
		//rect.setOrigin(ext.left, ext.top);

	  rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineThickness(outlineThick);
		rect.setOutlineColor(sf::Color::Red);
		target.draw(rect);
	}
}

const sf::Color& TShape::getRandColor()
{
	return TetrisShapes::shapeColors[GUtils::genRandomInt(0, shapeColors.size() - 1)];
}

sf::FloatRect TShape::getExtents() const {
	float xMax = 0.0, xMin = 1e10, yMax = 0.0, yMin = 1e10;
	for (auto& rect: m_rects) {
		sf::FloatRect curRect = rect.getGlobalBounds();
		if (curRect.left < xMin)
			xMin = curRect.left;
		if (curRect.left + curRect.width > xMax)
			xMax = curRect.left + curRect.width;
		if (curRect.top < yMin)
			yMin = curRect.top;
		if (curRect.top + curRect.height > yMax)
			yMax = curRect.top + curRect.height;
	}

	return sf::FloatRect(xMin, yMin, xMax - xMin, yMax - yMin);
}


void TShape::init() {
	const sf::Color& shapeColor = getRandColor();
	for (int i = 0; i < TetrisShapes::shapeParts; i++) {
		m_rects.push_back(sf::RectangleShape(sf::Vector2f(TetrisShapes::rectSize, TetrisShapes::rectSize)));
		m_rects.back().setFillColor(shapeColor);
		m_rects.back().setOutlineColor(sf::Color::Black);
		m_rects.back().setOutlineThickness(-TetrisShapes::outlineThick);
	}
}

void TShape::initI()
{
	m_rects[0].setPosition(center.x, center.y-rectSize/2);
	sf::Vector2f firstPos = m_rects[0].getPosition();
	m_rects[1].setPosition(firstPos.x + rectSize - outlineThick, firstPos.y);
	m_rects[2].setPosition(firstPos.x - rectSize + outlineThick, firstPos.y);
	m_rects[3].setPosition(firstPos.x - 2 * rectSize + 2*outlineThick,firstPos.y);

}

void TShape::initO()
{
	m_rects[0].setPosition(center);
	sf::Vector2f firstPos = m_rects[0].getPosition();
	m_rects[1].setPosition(firstPos.x - rectSize + outlineThick, firstPos.y);
	m_rects[2].setPosition(firstPos.x - rectSize + outlineThick, firstPos.y-rectSize + outlineThick);
	m_rects[3].setPosition(firstPos.x, firstPos.y - rectSize + outlineThick);
}

void TShape::initT()
{
	m_rects[0].setPosition(center.x-rectSize/2,center.y-rectSize/2);
	sf::Vector2f firstPos = m_rects[0].getPosition();
	m_rects[1].setPosition(firstPos.x + rectSize - outlineThick, firstPos.y);
	m_rects[2].setPosition(firstPos.x - rectSize + outlineThick, firstPos.y);
	m_rects[3].setPosition(firstPos.x, firstPos.y - rectSize + outlineThick);
}

void TShape::initZ()
{
	m_rects[0].setPosition(center.x - rectSize / 2, center.y - rectSize / 2);
	sf::Vector2f firstPos = m_rects[0].getPosition();
	m_rects[1].setPosition(firstPos.x + rectSize - outlineThick, firstPos.y);
	m_rects[2].setPosition(firstPos.x , firstPos.y - rectSize + outlineThick);
	m_rects[3].setPosition(firstPos.x - rectSize + outlineThick, firstPos.y - rectSize + outlineThick);
}
void TShape::initS()
{
	m_rects[0].setPosition(center.x - rectSize / 2, center.y - rectSize / 2);
	sf::Vector2f firstPos = m_rects[0].getPosition();
	m_rects[1].setPosition(firstPos.x - rectSize + outlineThick,firstPos.y);
	m_rects[2].setPosition(firstPos.x, firstPos.y - rectSize + outlineThick);
	m_rects[3].setPosition(firstPos.x + rectSize - outlineThick, firstPos.y - rectSize + outlineThick);
}

void TShape::initJ()
{
	m_rects[0].setPosition(center.x - rectSize / 2, center.y - rectSize / 2);
	sf::Vector2f firstPos = m_rects[0].getPosition();
	m_rects[1].setPosition(firstPos.x - rectSize + outlineThick, firstPos.y);
	m_rects[2].setPosition(firstPos.x + rectSize - outlineThick, firstPos.y);
	m_rects[3].setPosition(firstPos.x - rectSize + outlineThick, firstPos.y - rectSize + outlineThick);
}
void TShape::initL()
{
	m_rects[0].setPosition(center.x - rectSize / 2, center.y - rectSize / 2);
	sf::Vector2f firstPos = m_rects[0].getPosition();
	m_rects[1].setPosition(firstPos.x - rectSize + outlineThick, firstPos.y);
	m_rects[2].setPosition(firstPos.x + rectSize - outlineThick, firstPos.y);
	m_rects[3].setPosition(firstPos.x + rectSize - outlineThick, firstPos.y - rectSize + outlineThick);
}