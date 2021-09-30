#include "TField.h"
#include "../GUtils.h"
#include <stdio.h>
#include <iostream>
void TShape::init() {
    color = getRandColor();
    indices.resize(4);
}

TShape::TShape(int iType, const sf::Vector2i& iCenter) {
    type = iType;
    center = iCenter;
    init();
    switch (iType)
    {
        case TShapes::Type::I:
        {
            initI();
            break;
        }
        case TShapes::Type::O:
        {
            initO();
            break;
        }
        case TShapes::Type::T:
        {
            initT();
            break;
        }
        case TShapes::Type::Z:
        {
            initZ();
            break;
        }
        case TShapes::Type::S:
        {
            initS();
            break;
        }
        case TShapes::J:
        {
            initJ();
            break;
        }
        case TShapes::L:
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

void TShape::initI()
{
    indices[0] = {center.x, center.y-1};
    indices[1] = {center.x, center.y};
    indices[2] = {center.x, center.y+1};
    indices[3] = {center.x, center.y+2};
}

void TShape::initO()
{
    indices[0] = {center.x-1, center.y};
    indices[1] = {center.x, center.y};
    indices[2] = {center.x-1, center.y+1};
    indices[3] = {center.x, center.y+1};
}

void TShape::initT()
{
    indices[0] = {center.x, center.y-1};
    indices[1] = {center.x, center.y};
    indices[2] = {center.x-1, center.y};
    indices[3] = {center.x, center.y+1};
}
//max point at the left
void TShape::initZ()
{
    indices[0] = {center.x, center.y-1};
    indices[1] = {center.x, center.y};
    indices[2] = {center.x + 1, center.y };
    indices[3] = {center.x + 1, center.y + 1};
}
//max point at the right
void TShape::initS()
{
    indices[0] = {center.x, center.y-1};
    indices[1] = {center.x, center.y};
    indices[2] = {center.x - 1, center.y};
    indices[3] = {center.x - 1, center.y + 1};
}

void TShape::initJ()
{
    indices[0] = {center.x, center.y-1};
    indices[1] = {center.x, center.y};
    indices[2] = {center.x , center.y + 1};
    indices[3] = {center.x - 1, center.y + 1};
}
void TShape::initL()
{
    indices[0] = {center.x, center.y-1};
    indices[1] = {center.x, center.y};
    indices[2] = {center.x , center.y + 1};
    indices[3] = {center.x + 1, center.y + 1};
}
const sf::Color& TShape::getRandColor()
{
    return TShapes::shapeColors[GUtils::genRandomInt(0, TShapes::shapeColors.size() - 1)];
}

void TShape::move(const sf::Vector2i &iMotion) {
    for (auto& [x,y] : indices) {
        x += iMotion.x;
        y += iMotion.y;
    }
    center += iMotion;
}

TField::TField(int iWinWidth, int iWinHeight)
{
  fieldWidth = int((iWinWidth+2*TShapes::outlineThick)/ TShapes::rectSize);
  fieldHeight = int((iWinHeight+2*TShapes::outlineThick)/ TShapes::rectSize);
  grid.resize(fieldWidth);
	for (int i = 0; i < fieldWidth; i ++) {
    grid[i].resize(fieldHeight);
		for (int j = 0; j < fieldHeight; j ++) {
      //TODO: need new?
			auto* cell = new sf::RectangleShape(sf::Vector2f(TShapes::rectSize, TShapes::rectSize));
			cell->setPosition( i * TShapes::rectSize - TShapes::outlineThick, j * TShapes::rectSize-TShapes::outlineThick);
			cell->setFillColor(sf::Color::White);
			cell->setOutlineThickness(TShapes::outlineThick);
			cell->setOutlineColor(sf::Color::Black);
			grid[i][j] = (*cell);
		}
	}
    genRandTShape();
}
void TField::genRandTShape() {
    //TODO: new?
    TShape * rndShape = new TShape(GUtils::genRandomInt(0, TShapes::numTypes - 1));
    for (auto& [x,y] : rndShape->indices) {
        markRect(x,y,rndShape->color);
    }
    //TShape* rndShape = new TShape(TetrisShapes::J);
    shapes.push_back(*rndShape);
    //std::cout<<rndShape->type;
   // std::flush(std::cout);
}

void TField::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (const auto& row: grid) {
    for (const auto& cell: row)
		target.draw(cell);
	}
}

void TField::moveActiveShape(const sf::Vector2i &iMotion) {
    TShape& activeShape = *shapes.rbegin();

    activeShape.move(iMotion);
}
void TField::rotateActiveShape(bool iClockWise) {
    TShape& activeShape = *shapes.rbegin();
    if (activeShape.type == TShapes::Type::O)
        return;
    int dir = iClockWise ? 1 : -1;
    auto center = activeShape.center;
    for (auto& [x,y] : activeShape.indices){
        int X = y - center.y;
        int Y = x - center.x;
        x = center.x - X;
        y = center.y - Y;
    }
}
void TField::markRect(short i, short j, const sf::Color &iColor) {
    grid[i][j].setFillColor(iColor);
}

int TField::getMark(short i, short j) {
    sf::Color rectColor = grid[i][j].getFillColor();
    if (rectColor != sf::Color::Transparent){
        return Cell::Shape;
    }
    return Cell::Empty;
}

void TField::processEvent(float iTime, int iEventIdx) {
  const GEvent* event = events[iEventIdx];
  if (event->type == GEvent::EventType::Motion) {

  }
}

void TField::revertLastEvent() {

}

TField::~TField()
{
    //TODO: memory leaks?
    grid.clear();
}