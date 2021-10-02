#include "GTetris.h"
#
#include <iostream>
#include "TField.h"
#include "../GUtils.h"

GTetris::GTetris(int iWinWidth, int iWinHeight, float iFrameTime) {
	winWidth = iWinWidth;
	winHeight = iWinHeight;
	frameTime = iFrameTime;
  init();
	auto* field = new TField(iWinWidth, iWinHeight);
	objects.push_back(field);
}

void GTetris::init() {
  eventsPool.resize(7);
  eventsPool[Events::MoveLeft] = new GEventMotion(Tetris::left);
  eventsPool[Events::MoveRight] = new GEventMotion(Tetris::right);
  eventsPool[Events::MoveDown] = new GEventMotion(Tetris::down);
  eventsPool[Events::MoveEnd] = new GEvent(GEvent::EventType::MotionEnd);
  eventsPool[Events::MoveDown] = new GEventMotion(Tetris::down);
  eventsPool[Events::RotateStart] = new TRotationEventStart();
  eventsPool[Events::RotateEnd] = new TRotationEventEnd();
}

void GTetris::processKeys(const sf::Event& event, float iTime) {
  static float elapsedTime = 0.0;
  elapsedTime += iTime;
  if (elapsedTime > motionTime) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
      objects[0]->addEvent(eventsPool[Events::MoveLeft]);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      objects[0]->addEvent(eventsPool[Events::MoveRight]);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
      objects[0]->addEvent(eventsPool[Events::MoveDown]);
    }
    elapsedTime = 0.0;
  }
	if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::W) {
			objects[0]->addEvent(eventsPool[Events::RotateEnd]);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		objects[0]->addEvent(eventsPool[Events::RotateStart]);
	}
}
void GTetris::processEvents(float iTime) {
	elapsedTime += iTime;
	if (elapsedTime > fallTime) {
		objects[0]->addEvent(eventsPool[Events::MoveDown]);
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
}

GTetris::~GTetris() noexcept {
    for (auto * event : eventsPool){
        delete event;
    }
    for (auto * obj : objects){
        delete obj;
    }

}