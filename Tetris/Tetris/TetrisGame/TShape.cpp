#include "TShape.h"

Tetris::TShape::TShape(int iType, const sf::Vector2i& iCenter) : GObj(), type(iType) {
	switch (iType)
	{
	case ShapeType::Line:
		{
			initLine(iCenter);
			break;
		}
	case ShapeType::Rect:
		{
			initRect(iCenter);
			break;
		}
	case ShapeType::T:
		{
			initT(iCenter);
			break;
		}
	case ShapeType::ZigZagLeft:
		{
			initZigZagLeft(iCenter);
			break;
		}
	case ShapeType::ZigZagRight:
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
const std::vector<std::shared_ptr<sf::RectangleShape>>& Tetris::TShape::getRects() const {
	return m_rects;
}


void Tetris::TShape::initLine(const sf::Vector2i& iCenter)
{
	center = iCenter;
	for (int i = 0; i < Tetris::shapeParts; i++) {
		m_rects.push_back(std::make_shared<sf::RectangleShape>(sf::Vector2f(50,50)));
		m_rects.back()->setFillColor(sf::Color::Cyan);
		m_rects.back()->setOutlineColor(sf::Color::Magenta);
		m_rects.back()->setOutlineThickness(1);
	}
	m_rects[0]->setPosition(center.x + 25.0, center.y);
	m_rects[1]->setPosition(center.x + 75.0, center.y);
	m_rects[2]->setPosition(center.x - 25.0, center.y);
	m_rects[3]->setPosition(center.x - 75.0, center.y);

}

void Tetris::TShape::initRect(const sf::Vector2i& iCenter)
{
	
}

void Tetris::TShape::initT(const sf::Vector2i& iCenter)
{
	
}

void Tetris::TShape::initZigZagLeft(const sf::Vector2i& iCenter)
{
	
}
void Tetris::TShape::initZigZagRight(const sf::Vector2i& iCenter)
{
	
}
