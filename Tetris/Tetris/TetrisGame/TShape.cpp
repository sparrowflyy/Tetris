#include "TShape.h"

TShape::TShape(int iType, const sf::Vector2i& iCenter) : GObj(), type(iType) {
	parts = 4;
	switch (iType)
	{
	case Tetris::ShapeType::Line:
		{
			initLine(iCenter);
			break;
		}
	case Tetris::ShapeType::Rect:
		{
			initRect(iCenter);
			break;
		}
	case Tetris::ShapeType::T:
		{
			initT(iCenter);
			break;
		}
	case Tetris::ShapeType::ZigZagLeft:
		{
			initZigZagLeft(iCenter);
			break;
		}
	case Tetris::ShapeType::ZigZagRight:
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






const sf::Drawable* TShape::getDrawable(int idx) const {
	return m_rects[idx].get();
}

void TShape::initLine(const sf::Vector2i& iCenter)
{
	center = iCenter;
	for (int i = 0; i < Tetris::shapeParts; i++) {
		m_rects.push_back(std::make_shared<sf::RectangleShape>(sf::Vector2f(Tetris::rectSize,Tetris::rectSize)));
		m_rects.back()->setFillColor(sf::Color::Cyan);
		m_rects.back()->setOutlineColor(sf::Color::Magenta);
		m_rects.back()->setOutlineThickness(-Tetris::outlineThick);
	}
	m_rects[0]->setPosition(center.x - 3 * Tetris::rectSize / 2, center.y);
	m_rects[1]->setPosition(center.x - Tetris::rectSize / 2, center.y);
	m_rects[2]->setPosition(center.x + Tetris::rectSize/2 , center.y);
	m_rects[3]->setPosition(center.x + 3*Tetris::rectSize/2, center.y);

	

}

void TShape::initRect(const sf::Vector2i& iCenter)
{
	
}

void TShape::initT(const sf::Vector2i& iCenter)
{
	
}

void TShape::initZigZagLeft(const sf::Vector2i& iCenter)
{
	
}
void TShape::initZigZagRight(const sf::Vector2i& iCenter)
{
	
}
