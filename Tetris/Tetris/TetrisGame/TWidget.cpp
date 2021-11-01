//
// Created by nik on 10.10.2021.
//
#include "TWidget.h"

void TWidget::initMiniGrid() {
  squareFieldSize = 4;
  float startX,startY;
  startX = rect.left + rectSize;
  startY = rect.top + rect.height * 0.2;
  miniGrid.resize(squareFieldSize);
  for (int i = 0; i < squareFieldSize; i ++) {
    miniGrid[i].resize(squareFieldSize);
    for (int j = 0; j < squareFieldSize; j ++) {
      auto cell = std::make_shared<sf::RectangleShape>(sf::Vector2f(rectSize,rectSize));
      cell->setFillColor(sf::Color::White);
      cell->setPosition( startX + i * rectSize, startY + j * rectSize);
      cell->setOutlineThickness(-TShapes::outlineThick);
      cell->setOutlineColor(sf::Color::Black);
      miniGrid[i][j] = cell;
    }
  }
}
TWidget::TWidget(int iLeft, int iTop, int iWidth, int iHeight, float iRectSize)
  : rect(iLeft,iTop,iWidth,iHeight)
{
  texts.resize(6); //enum size
  rectSize = iRectSize;
  font.loadFromFile(fontFilename);
  sf::Text gameName ("Tetris",font);
  gameName.setFillColor(sf::Color::White);
  gameName.setCharacterSize(fontSize);
  auto bound = gameName.getLocalBounds();
  gameName.setPosition(rect.left + rect.width/2 - bound.width/2,rect.top + bound.height);

  sf::Text scoreName("Score:",font);
  scoreName.setFillColor(sf::Color::White);
  scoreName.setCharacterSize(fontSize);
  bound = scoreName.getLocalBounds();
  scoreName.setPosition(rect.left + rect.width/2 - bound.width/2,rect.top + rect.height*0.5-bound.height);

  sf::Text score("0",font);
  score.setFillColor(sf::Color::White);
  bound = score.getLocalBounds();
  score.setPosition(rect.left + rect.width/2 - bound.width/2,rect.top + rect.height*0.6-bound.height);

  texts[GameName] = gameName;
  texts[ScoreName] = scoreName;
  texts[Score] = score;

  initMiniGrid();

}

void TWidget::markNextShape() {
  for (int i = 0; i < squareFieldSize; i++){
    for (int j = 0; j < squareFieldSize; j++){
      miniGrid[i][j]->setFillColor(sf::Color::Black);
    }
  }
  int type = nextShape->type;
  switch (type) {
    case TShapes::Type::I: {
      miniGrid[3][0]->setFillColor(nextShape->color);
      miniGrid[3][1]->setFillColor(nextShape->color);
      miniGrid[3][2]->setFillColor(nextShape->color);
      miniGrid[3][3]->setFillColor(nextShape->color);
      break;
    }
    case TShapes::Type::J: {
      miniGrid[3][1]->setFillColor(nextShape->color);
      miniGrid[3][2]->setFillColor(nextShape->color);
      miniGrid[3][3]->setFillColor(nextShape->color);
      miniGrid[2][3]->setFillColor(nextShape->color);
      break;
    }
    case TShapes::Type::L: {
      miniGrid[2][1]->setFillColor(nextShape->color);
      miniGrid[2][2]->setFillColor(nextShape->color);
      miniGrid[2][3]->setFillColor(nextShape->color);
      miniGrid[3][3]->setFillColor(nextShape->color);
      break;
    }
    case TShapes::Type::O: {
      miniGrid[2][1]->setFillColor(nextShape->color);
      miniGrid[2][2]->setFillColor(nextShape->color);
      miniGrid[3][1]->setFillColor(nextShape->color);
      miniGrid[3][2]->setFillColor(nextShape->color);
      break;
    }
    case TShapes::Type::T: {
      miniGrid[3][1]->setFillColor(nextShape->color);
      miniGrid[3][2]->setFillColor(nextShape->color);
      miniGrid[3][3]->setFillColor(nextShape->color);
      miniGrid[2][2]->setFillColor(nextShape->color);
      break;
    }
    case TShapes::Type::S: {
      miniGrid[3][1]->setFillColor(nextShape->color);
      miniGrid[3][2]->setFillColor(nextShape->color);
      miniGrid[2][2]->setFillColor(nextShape->color);
      miniGrid[2][3]->setFillColor(nextShape->color);
      break;
    }
    case TShapes::Type::Z: {
      miniGrid[2][1]->setFillColor(nextShape->color);
      miniGrid[2][2]->setFillColor(nextShape->color);
      miniGrid[3][2]->setFillColor(nextShape->color);
      miniGrid[3][3]->setFillColor(nextShape->color);
      break;
    }
  }
}
void TWidget::setNextTShape(std::shared_ptr<TShape> iNextShape) {
  nextShape = iNextShape;
  markNextShape();
}
void TWidget::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  for (const auto& text: texts){
    target.draw(text);
  }
  for (const auto& row: miniGrid) {
    std::for_each(row.begin(), row.end(), [&](const std::shared_ptr<sf::RectangleShape> rect) { target.draw(*rect); });
  }
}

void TWidget::processEvent(float iTime, int iEventIdx) {
 std::shared_ptr<GEvent> event = events[iEventIdx];
  if (event->type == GEvent::EventType::Text) {
    std::shared_ptr<GEventText> textEvent = std::static_pointer_cast<GEventText>(event);
    texts[Score].setString(textEvent->string);
    auto bound =  texts[Score].getLocalBounds();
    texts[Score].setPosition(rect.left + rect.width/2 - bound.width/2,rect.top + rect.height*0.6-bound.height);

  }
}
