#include "TField.h"
#include "../GUtils.h"
#include <stdio.h>
#include <iostream>
#include <memory>
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
  rectSize = (iWinWidth)/fieldWidth;
  fieldHeight = int(iWinHeight/rectSize) + bufferSize;
  grid.resize(fieldWidth);
	for (int i = 0; i < fieldWidth; i ++) {
    grid[i].resize(fieldHeight);
		for (int j = 0; j < fieldHeight; j ++) {
			auto cell = std::make_shared<sf::RectangleShape>(sf::Vector2f(rectSize,rectSize));
			cell->setPosition( i * rectSize, (j-bufferSize) * rectSize);
      cell->setFillColor(backgroundColor);
      if (j < bufferSize-1){

        grid[i][j] = cell;
        continue;
      }

			cell->setOutlineThickness(-TShapes::outlineThick);
			cell->setOutlineColor(sf::Color::Black);
      grid[i][j] = cell;

		}
	}
  genRandTShape();
}
void TField::genRandTShape() {
  if (nextShape == nullptr){
    nextShape = std::make_shared<TShape>(GUtils::genRandomInt(0, TShapes::numTypes - 1));
  }
  activeShape = nextShape;
  nextShape = std::make_shared<TShape>(GUtils::genRandomInt(0, TShapes::numTypes - 1));
  for (auto& [x,y] : activeShape->indices) {
    markRect(x,y,activeShape->color);
  }
}

void TField::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (const auto& row: grid) {
    std::for_each(row.begin(), row.end(), [&](const std::shared_ptr<sf::RectangleShape> rect) { target.draw(*rect); });
  }
}

void TField::markRect(short i, short j, const sf::Color &iColor) {
    grid[i][j]->setFillColor(iColor);
}

int TField::getMark(short i, short j) {
    if (i < 0 || i >= fieldWidth || j < 0 || j >=fieldHeight ) {
      return Cell::Empty;
    }
    sf::Color rectColor = grid[i][j]->getFillColor();
    auto found = std::find(TShapes::shapeColors.begin(), TShapes::shapeColors.end(), rectColor);
    if (found == TShapes::shapeColors.end()){
        return Cell::Empty;
    }
    return Cell::Shape;
}

bool TField::checkShape(TShape &iShape) {
  for (int i = 0; i < iShape.indices.size(); i++) {
    int x = iShape.indices[i].first;
    int y = iShape.indices[i].second;
    if (x < 0 || x > fieldWidth - 1)
      return false;
    if (y > fieldHeight - 1) {
      activeShape->alive = false;
      return false;
    }
    if (getMark(x,y) == Cell::Shape) {
      if (activeShape->indices[i].second < y && !iShape.rotating) {
        activeShape->alive = false;
      }
      return false;
    }


  }
  return true;
}
void TField::processEvent(float iTime, int iEventIdx) {
  static float elapsedTime = 0.0;
  elapsedTime+=iTime;
  TShape activeShapeCopy = *activeShape.get();
  for (auto& [x,y]:activeShape->indices){
    markRect(x,y);
  }
  std::shared_ptr<GEvent> event = events[iEventIdx];
  if (event->type == GEvent::EventType::MotionStart) {
    std::shared_ptr<GEventMotion<int>> motionEvent = std::static_pointer_cast<GEventMotion<int>>(event);
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
    activeShape = std::make_unique<TShape>(activeShapeCopy);
  }
  for (auto& [x,y]:activeShape->indices){
    markRect(x,y,activeShape->color);
  }
}

void TField::copyRowColors(int iRow, int iDestRow) {
  for (int i = 0; i < fieldWidth; i++) {
    grid[i][iDestRow]->setFillColor(grid[i][iRow]->getFillColor());
  }
}
void TField::checkField() {
  int filledCells = 0;
  std::vector<int> rowsToRemove;
  for (int j = 0; j < fieldHeight; j ++) {
    filledCells = 0;
    for (int i = 0; i < fieldWidth; i++){
      if (getMark(i,j) == Cell::Empty)
        break;
      ++filledCells;
    }
    if (filledCells == fieldWidth) {
      if (j == 0) {
        //TODO:: GAME OVER!
        return;
      }
      rowsToRemove.push_back(j);
    }
  }
  if (rowsToRemove.empty())
    return;
  //bug at the right corner
  int start = *rowsToRemove.begin();
  int end = *rowsToRemove.rbegin();
  int length = end - start;
  score+=(1+length*2)*100;
  for (int i = start - 1; i > 0; i-- ) {
    copyRowColors(i,i+length+1);
    copyRowColors(0,i);
  }
  for (int j = start; j < bufferSize + length + 1 ; j++) {
    for (int i = 0; i < fieldWidth; i++) {
      markRect(i,j);
    }
  }
}
void TField::revertLastEvent() {

}

TField::~TField()
{
  for (auto& rows : grid){
    rows.clear();
  }
  grid.clear();
}