#include "GTetris.h"
#include <memory>
#include <iostream>
#include "TField.h"
#include "../GUtils.h"
#include "TBackground.h"
#include "TWidget.h"

GTetris::GTetris(int iWinWidth, int iWinHeight, float iFrameTime) {
	winWidth = iWinWidth;
	winHeight = iWinHeight;
	frameTime = iFrameTime;
  objects.resize(objectsCount);
  init();
  isGameOver = false;
  isGameStarted = false;
  std::vector<std::string> filenames = {"/home/nik/c++/Tetris/Tetris/Tetris/TetrisGame/Data/back.png"};
  auto background = std::make_shared<TBackground>(winWidth - widgetSize,winHeight, filenames);
  objects[Background] = background;
  std::shared_ptr<TField> field = std::static_pointer_cast<TField>(objects[Objects::Field]);
  auto widget = std::make_shared<TWidget>(winWidth ,winHeight,widgetSize,field->rectSize);
  objects[Widget] = widget;
  widget->setNextTShape(field->nextShape);
  eventsPool.resize(7);
  eventsPool[Events::MoveLeft] = std::make_shared<GEventMotion<int>>(Tetris::left);
  eventsPool[Events::MoveRight] = std::make_shared<GEventMotion<int>>(Tetris::right);
  eventsPool[Events::MoveDown] = std::make_shared<GEventMotion<int>>(Tetris::down);
  eventsPool[Events::MoveEnd] = std::make_shared<GEvent>(GEvent::EventType::MotionEnd);
  eventsPool[Events::RotateStart] = std::make_shared<TRotationEventStart>();
  eventsPool[Events::RotateEnd] = std::make_shared<TRotationEventEnd>();
  eventsPool[Events::ScoreUpdate] = std::make_shared<GEventText>("0");
}

void GTetris::init() {
  auto field = std::make_shared<TField>(winWidth - widgetSize, winHeight);
  objects[Field] = field;

}

void GTetris::drawObjects(sf::RenderTarget &target, sf::RenderStates states) {
  for (auto& obj : objects) {
    obj->draw(target, sf::RenderStates::Default);
  }
}

void GTetris::processKeys(const sf::Event& event, float iTime) {
  static float elapsedTime = 0.0;
  elapsedTime += iTime;
  if (!isGameStarted) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
      isGameStarted = true;
      std::shared_ptr<TWidget> widget = std::static_pointer_cast<TWidget>(objects[Objects::Widget]);
      widget->setState(TWidget::State::Game);
    }
    elapsedTime = 0.0;
    return;
  }
  if (isGameOver){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
      isGameOver = false;
      init();
      std::shared_ptr<TField> field = std::static_pointer_cast<TField>(objects[Objects::Field]);
      std::shared_ptr<TWidget> widget = std::static_pointer_cast<TWidget>(objects[Objects::Widget]);
      widget->setNextTShape(field->nextShape);
      widget->setState(TWidget::State::Game);
    }
    elapsedTime = 0.0;
    return;
  }

  if (elapsedTime > motionTime) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
      objects[Objects::Field]->addEvent(eventsPool[Events::MoveLeft]);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      objects[Objects::Field]->addEvent(eventsPool[Events::MoveRight]);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
      objects[Objects::Field]->addEvent(eventsPool[Events::MoveDown]);
    }
    elapsedTime = 0.0;
  }
	if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::W) {
			objects[Objects::Field]->addEvent(eventsPool[Events::RotateEnd]);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		objects[Objects::Field]->addEvent(eventsPool[Events::RotateStart]);
	}
}
void GTetris::processEvents(float iTime) {
  if (!isGameStarted || isGameOver){
    return;
  }
	elapsedTime += iTime;
	if (elapsedTime > fallTime) {
		objects[Objects::Field]->addEvent(eventsPool[Events::MoveDown]);
		elapsedTime = 0.0;
	}
  for (auto & obj : objects) {
    for (int i = 0; i < obj->events.size(); i++) {
      obj->processEvent(iTime, i);
    }
    obj->events.clear();
  }
}
void GTetris::postProcess() {
  if (!isGameStarted || isGameOver){
    return;
  }
  std::shared_ptr<TField> field = std::static_pointer_cast<TField>(objects[Objects::Field]);
  std::shared_ptr<TWidget> widget = std::static_pointer_cast<TWidget>(objects[Objects::Widget]);
  if (!field->activeShape->alive) {
    currentScore = field->score;
    isGameOver = field->isGameOver();
    if (isGameOver){
      widget->setState(TWidget::State::GameIsOver);
      return;
    }
    field->checkField();
    field->genRandTShape();

    widget->setNextTShape(field->nextShape);
    if (currentScore - lastScore >= 1000) {
      lastScore = currentScore;
      fallTime -= 0.01;
      motionTime -= 0.001;
    }
  }
  std::static_pointer_cast<GEventText>(eventsPool[Events::ScoreUpdate])->setString(std::to_string(field->score));
  objects[Objects::Widget]->addEvent(eventsPool[Events::ScoreUpdate]);
}

GTetris::~GTetris() noexcept {

}