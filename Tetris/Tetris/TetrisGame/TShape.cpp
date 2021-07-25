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

void TShape::update(float iTime)
{
	elapsedTime += iTime;
	if (elapsedTime > fallTime) {
		addEvent(new GEventMotion(Tetris::down * float(TetrisShapes::rectSize)/iTime));
		elapsedTime = 0.0;
	}
	for (int i = 0; i < m_events.size(); i++) {

		if (m_events[i]->type == GEvent::EventType::RotationEnd && rotated) {
			rotated = false;
		}
		if (m_events[i]->type == GEvent::EventType::RotationStart && !rotated) {
			rotated = true;
			rotate();
		}
		if (m_events[i]->type == GEvent::EventType::Motion) {
			GEventMotion* event = (GEventMotion*)(m_events[i]);
			const sf::Vector2f& motion = event->getMotion() * iTime;
			for (int rectIdx = 0; rectIdx < TetrisShapes::shapeParts; rectIdx++) {
				m_rects[rectIdx].move(motion);
			}
			center.x += motion.x;
			center.y += motion.y;
		}

	}
	m_events.clear();
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
			xMax = curRect.left;
		if (curRect.top < yMin)
			yMin = curRect.top;
		if (curRect.top + curRect.height > yMax)
			yMax = curRect.top + curRect.height;
	}
	return sf::FloatRect(xMin,yMin,xMax-xMin, yMax - yMin);
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