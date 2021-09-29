#include "GTetris.h"
#
#include <iostream>
#include "TField.h"
#include "../GUtils.h"

GTetris::GTetris(int iWinWidth, int iWinHeight, float iFrameTime) {
	winWidth = iWinWidth;
	winHeight = iWinHeight;
	frameTime = iFrameTime;
	auto* field = new TField(iWinWidth, iWinHeight);
	objects.push_back(field);
}

void GTetris::init() {
    eventsPool.resize(5);
    eventsPool[Events::MoveLeft] = new GEventMotion(Tetris::left);
    eventsPool[Events::MoveRight] = new GEventMotion(Tetris::right);
    eventsPool[Events::MoveDown] = new GEventMotion(Tetris::right);
    eventsPool[Events::RotateStart] = new TRotationEventStart();
    eventsPool[Events::RotateEnd] = new TRotationEventEnd();
}

void GTetris::processKeys(const sf::Event& event) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		objects[fieldIdx]->addEvent(eventsPool[Events::MoveLeft]);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        objects[fieldIdx]->addEvent(eventsPool[Events::MoveRight]);
	}
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        objects[fieldIdx]->addEvent(eventsPool[Events::MoveDown]);
    }
	if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::W) {
			objects[fieldIdx]->addEvent(eventsPool[Events::RotateEnd]);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		objects[fieldIdx]->addEvent(eventsPool[Events::RotateStart]);
	}

}

void GTetris::processEvents(float iTime) {
	elapsedTime += iTime;
	if (elapsedTime > fallTime) {
		objects[fieldIdx]->addEvent(eventsPool[Events::MoveDown]);
		elapsedTime = 0.0;
	}
    for (auto & obj : objects) {
        for (int i = 0; i < obj->events.size(); i++) {
            obj->processEvent(iTime, i);
        }
        obj->events.clear();
    }
/*	for (auto & obj : objects) {
		auto* curShape = (TShape*)obj;

	objIdx->m_events.clear();
	}*/
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