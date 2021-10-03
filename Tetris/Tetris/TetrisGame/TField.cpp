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

void TShape::rotate() {
  if (type == TShapes::Type::O)
    return;
  for (auto& [x,y] : indices){
    int Y = y - center.y;
    int X = x - center.x;
    x = center.x - Y;
    y = center.y + X;
  }
  rotating = true;
}
TField::TField(int iWinWidth, int iWinHeight)
{
  int bufferSize = 3;
  float rectSize = (iWinWidth)/fieldWidth;
  fieldHeight = int(iWinHeight/rectSize) + bufferSize;
  grid.resize(fieldWidth);

	for (int i = 0; i < fieldWidth; i ++) {
    grid[i].resize(fieldHeight);
		for (int j = 0; j < fieldHeight; j ++) {
			auto* cell = new sf::RectangleShape(sf::Vector2f(rectSize,rectSize));
      if (j <= bufferSize){
        cell->setFillColor(backgroundColor);
        grid[i][j] = (*cell);
        continue;
      }
			cell->setPosition( i * rectSize, (j - bufferSize) * rectSize);
			cell->setFillColor(sf::Color::White);
			cell->setOutlineThickness(-TShapes::outlineThick);
			cell->setOutlineColor(sf::Color::Black);
      grid[i][j] = (*cell);
		}
	}
    genRandTShape();
}
void TField::genRandTShape() {
    //TODO: new
    TShape * rndShape = new TShape(GUtils::genRandomInt(0, TShapes::numTypes - 1));
    for (auto& [x,y] : rndShape->indices) {
        markRect(x,y,rndShape->color);
    }
    shapes.push_back(*rndShape);
}

void TField::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (const auto& row: grid) {
    std::for_each(row.begin(), row.end(), [&](const sf::RectangleShape &rect) { target.draw(rect); });
  }
}

void TField::markRect(short i, short j, const sf::Color &iColor) {
    grid[i][j].setFillColor(iColor);
}

int TField::getMark(short i, short j) {
    if (i < 0 || i >= fieldWidth || j < 0 || j >=fieldHeight ) {
      return Cell::Empty;
    }
    sf::Color rectColor = grid[i][j].getFillColor();
    auto found = std::find(TShapes::shapeColors.begin(), TShapes::shapeColors.end(), rectColor);
    if (found == TShapes::shapeColors.end()){
        return Cell::Empty;
    }
    return Cell::Shape;
}

bool TField::checkShape(TShape &iShape) {
  auto& activeShape = *shapes.rbegin();
  for (int i = 0; i < iShape.indices.size(); i++) {
    int x = iShape.indices[i].first;
    int y = iShape.indices[i].second;
    if (x < 0 || x > fieldWidth - 1)
      return false;
    if (y > fieldHeight - 1) {
      activeShape.alive = false;
      return false;
    }
    if (getMark(x,y) == Cell::Shape) {
      if (activeShape.indices[i].second < y) {
        activeShape.alive = false;
      }
      return false;
    }


  }
  return true;
}
void TField::processEvent(float iTime, int iEventIdx) {
  static float elapsedTime = 0.0;
  elapsedTime+=iTime;
  TShape& activeShape = *shapes.rbegin();
  TShape activeShapeCopy = *shapes.rbegin();
  for (auto& [x,y]:activeShape.indices){
    markRect(x,y);
  }
  const GEvent* event = events[iEventIdx];
  if (event->type == GEvent::EventType::MotionStart) {
    auto* motionEvent = (GEventMotion<int>*)event;
    activeShapeCopy.move(motionEvent->getMotion());
  }
  if (event->type == GEvent::EventType::MotionEnd && activeShapeCopy.moving) {
    activeShapeCopy.moving = false;
  }
  if (event->type == GEvent::EventType::RotationStart && !activeShapeCopy.rotating) {
    activeShapeCopy.rotate();
  }
  if (event->type == GEvent::EventType::RotationEnd && activeShapeCopy.rotating) {
    activeShapeCopy.rotating = false;
  }
  if (checkShape(activeShapeCopy)){
    activeShape = activeShapeCopy;
  }
  for (auto& [x,y]:activeShape.indices){
    markRect(x,y,activeShape.color);
  }

  if (activeShape.alive == false) {
    genRandTShape();
  }

}

void TField::revertLastEvent() {

}

TField::~TField()
{
  grid.clear();
}