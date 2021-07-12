#include "TShape.h"

#include <random>

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



const sf::Color& TShape::getRandColor()
{
	std::random_device rd;  
	std::mt19937 gen(rd()); 
	std::uniform_int_distribution<> distrib(0, Tetris::shapeColors.size()-1);

	return Tetris::shapeColors[distrib(gen)];
}

const sf::Drawable* TShape::getDrawable(int idx) const {
	return m_rects[idx].get();
}

void TShape::initRectangles() {
	const sf::Color& shapeColor = getRandColor();
	for (int i = 0; i < Tetris::shapeParts; i++) {
		m_rects.push_back(std::make_shared<sf::RectangleShape>(sf::Vector2f(Tetris::rectSize, Tetris::rectSize)));
		m_rects.back()->setFillColor(shapeColor);
		m_rects.back()->setOutlineColor(sf::Color::Black);
		m_rects.back()->setOutlineThickness(-Tetris::outlineThick);
	}
}

void TShape::initLine(const sf::Vector2i& iCenter)
{
	center = iCenter;
	initRectangles();
	m_rects[0]->setPosition(center.x - 3 * Tetris::rectSize / 2, center.y);
	for (int i = 1; i < 4; i++) {
		m_rects[i]->setPosition(m_rects[i-1]->getPosition().x - Tetris::outlineThick  + Tetris::rectSize, center.y);
	}
	

}

void TShape::initRect(const sf::Vector2i& iCenter)
{
	center = iCenter;
	initRectangles();
	m_rects[0]->setPosition(center.x - Tetris::rectSize / 2, center.y);
	m_rects[1]->setPosition(m_rects[0]->getPosition().x - Tetris::outlineThick + Tetris::rectSize, center.y);
	m_rects[2]->setPosition(center.x - Tetris::rectSize / 2 , center.y - Tetris::outlineThick + Tetris::rectSize);
	m_rects[3]->setPosition(m_rects[2]->getPosition().x - Tetris::outlineThick + Tetris::rectSize, center.y - Tetris::outlineThick + Tetris::rectSize);
}

void TShape::initT(const sf::Vector2i& iCenter)
{
	center = iCenter;
	initRectangles();
	m_rects[0]->setPosition(center.x , center.y);
	m_rects[1]->setPosition(center.x , center.y - Tetris::outlineThick + Tetris::rectSize);
	m_rects[2]->setPosition(center.x - Tetris::rectSize + Tetris::outlineThick, center.y - Tetris::outlineThick + Tetris::rectSize);
	m_rects[3]->setPosition(center.x + Tetris::rectSize - Tetris::outlineThick, center.y - Tetris::outlineThick + Tetris::rectSize);
}

void TShape::initZigZagLeft(const sf::Vector2i& iCenter)
{
	center = iCenter;
	initRectangles();
	m_rects[0]->setPosition(center.x - Tetris::rectSize / 2, center.y);
	m_rects[1]->setPosition(m_rects[0]->getPosition().x - Tetris::outlineThick + Tetris::rectSize, center.y);
	m_rects[2]->setPosition(center.x + Tetris::rectSize / 2 - Tetris::outlineThick, center.y - Tetris::outlineThick + Tetris::rectSize);
	m_rects[3]->setPosition(m_rects[2]->getPosition().x - Tetris::outlineThick + Tetris::rectSize, center.y - Tetris::outlineThick + Tetris::rectSize);
}
void TShape::initZigZagRight(const sf::Vector2i& iCenter)
{
	center = iCenter;
	initRectangles();
	m_rects[0]->setPosition(center.x + Tetris::rectSize / 2, center.y);
	m_rects[1]->setPosition(m_rects[0]->getPosition().x - Tetris::outlineThick + Tetris::rectSize, center.y);
	m_rects[2]->setPosition(center.x + Tetris::rectSize/2 , center.y - Tetris::outlineThick + Tetris::rectSize);
	m_rects[3]->setPosition(m_rects[2]->getPosition().x + Tetris::outlineThick - Tetris::rectSize, center.y - Tetris::outlineThick + Tetris::rectSize);

}
