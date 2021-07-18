#include "TShape.h"

#include <random>

#include "GTetris.h"
#include "../GUtils.h"

TShape::TShape(int iType, const sf::Vector2f& iCenter) {
	parts = 4;
	type = -1;
	center = iCenter;
	init();
	switch (iType)
		{
		case TetrisShapes::ShapeType::Line:
			{
				initLine(iCenter);
				break;
			}
		case TetrisShapes::ShapeType::Rect:
			{
				initRect(iCenter);
				break;
			}
		case TetrisShapes::ShapeType::T:
			{
				initT(iCenter);
				break;
			}
		case TetrisShapes::ShapeType::ZigZagLeft:
			{
				initZigZagLeft(iCenter);
				break;
			}
		case TetrisShapes::ShapeType::ZigZagRight:
			{
				initZigZagRight(iCenter);
				break;
			}
			default:
			{
				break;
			}
		}
}
void TShape::rotate()
{
	for (int i = 0; i < TetrisShapes::shapeParts; i++) {
		sf::Vector2f pos = m_rects[i].getPosition();
		float x = pos.y - center.y;
		float y = pos.x - center.x;
		pos.x = center.x - x;
		pos.y = center.y + y;
		m_rects[i].setPosition(pos);
	}
}




void TShape::update(float iTime)
{
	m_events.push_back(new GEventMotion(Tetris::down * float(TetrisShapes::rectSize)));
	for (int i = 0; i < m_events.size(); i++) {
		if (m_events[i]->type == GEvent::EventType::Motion) {
			GEventMotion* event = (GEventMotion*)(m_events[i]);
			const sf::Vector2f& motion = event->getMotion() * iTime;
			for (int rectIdx = 0; rectIdx < TetrisShapes::shapeParts; rectIdx++) {
				m_rects[rectIdx].move(motion);
			}
			if (event->getAngle() != 0.0) {
				rotate();
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
	return TetrisShapes::shapeColors[GUtils::genRandomInt(0, TetrisShapes::shapeColors.size() - 1)];
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

void TShape::initLine(const sf::Vector2f& iCenter)
{

	m_rects[0].setPosition(center.x - 3 * TetrisShapes::rectSize / 2, center.y);
	for (int i = 1; i < 4; i++) {
		m_rects[i].setPosition(m_rects[i-1].getPosition().x - TetrisShapes::outlineThick  + TetrisShapes::rectSize, center.y);
	}
	

}

void TShape::initRect(const sf::Vector2f& iCenter)
{
	m_rects[0].setPosition(center.x - TetrisShapes::rectSize / 2, center.y);
	m_rects[1].setPosition(m_rects[0].getPosition().x - TetrisShapes::outlineThick + TetrisShapes::rectSize, center.y);
	m_rects[2].setPosition(center.x - TetrisShapes::rectSize / 2 , center.y - TetrisShapes::outlineThick + TetrisShapes::rectSize);
	m_rects[3].setPosition(m_rects[2].getPosition().x - TetrisShapes::outlineThick + TetrisShapes::rectSize, center.y - TetrisShapes::outlineThick + TetrisShapes::rectSize);
}

void TShape::initT(const sf::Vector2f& iCenter)
{
	m_rects[0].setPosition(center.x, center.y - TetrisShapes::rectSize + TetrisShapes::outlineThick);
	m_rects[1].setPosition(center);
	m_rects[2].setPosition(m_rects[1].getPosition().x + TetrisShapes::rectSize - TetrisShapes::outlineThick, m_rects[1].getPosition().y);
	m_rects[3].setPosition(m_rects[1].getPosition().x - TetrisShapes::rectSize + TetrisShapes::outlineThick, m_rects[1].getPosition().y);
}

void TShape::initZigZagLeft(const sf::Vector2f& iCenter)
{
	m_rects[1].setPosition(center);
	m_rects[0].setPosition(m_rects[1].getPosition().x + TetrisShapes::rectSize - TetrisShapes::outlineThick, m_rects[1].getPosition().y);
	m_rects[2].setPosition(m_rects[1].getPosition().x, m_rects[1].getPosition().y + TetrisShapes::outlineThick - TetrisShapes::rectSize);
	m_rects[3].setPosition(m_rects[2].getPosition().x + TetrisShapes::outlineThick - TetrisShapes::rectSize, m_rects[2].getPosition().y);
}
void TShape::initZigZagRight(const sf::Vector2f& iCenter)
{
	m_rects[0].setPosition(center.x + TetrisShapes::rectSize / 2, center.y);
	m_rects[1].setPosition(m_rects[0].getPosition().x - TetrisShapes::outlineThick + TetrisShapes::rectSize, center.y);
	m_rects[2].setPosition(center.x + TetrisShapes::rectSize/2 , center.y - TetrisShapes::outlineThick + TetrisShapes::rectSize);
	m_rects[3].setPosition(m_rects[2].getPosition().x + TetrisShapes::outlineThick - TetrisShapes::rectSize, center.y - TetrisShapes::outlineThick + TetrisShapes::rectSize);

}
