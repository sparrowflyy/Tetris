//
// Created by nik on 10.10.2021.
//
#include "TWidgetScore.h"
//TODO: Draw next shape
TWidgetScore::TWidgetScore(int iLeft, int iTop, int iWidth, int iHeight)
  : rect(iLeft,iTop,iWidth,iHeight)
{
  //TODO: ивенты просто с текстом что делать
  //TODO: exceptions
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

  texts.push_back(gameName);
  texts.push_back(scoreName);
  texts.push_back(score);


}

void TWidgetScore::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  for (const auto& text: texts){
    target.draw(text);
  }
}

void TWidgetScore::processEvent(float iTime, int iEventIdx) {
 std::shared_ptr<GEvent> event = events[iEventIdx];
  if (event->type == GEvent::EventType::Text) {
    std::shared_ptr<GEventText> textEvent = std::static_pointer_cast<GEventText>(event);
    texts.back().setString(textEvent->string);
    auto bound =  texts.back().getLocalBounds();
    texts.back().setPosition(rect.left + rect.width/2 - bound.width/2,rect.top + rect.height*0.6-bound.height);

  }
}
