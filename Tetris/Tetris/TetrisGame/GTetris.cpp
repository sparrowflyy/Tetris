#include "GTetris.h"
#
#include <iostream>

#include "../GUtils.h"

void GTetris::genRandTShape() {
	TShape* rndShape = new TShape(GUtils::genRandomInt(0, TetrisShapes::numTypes - 1));
	m_obj.push_back(rndShape);
}

void GTetris::init() {
	m_events.resize(4);

	m_events[Events::MoveLeft] = new GEventMotion(Tetris::left* TetrisShapes::shapeSpeed);
	m_events[Events::MoveRight] = new GEventMotion(Tetris::right * TetrisShapes::shapeSpeed);
	m_events[Events::RotateStart] = new TRotationEventStart();
	m_events[Events::RotateEnd] = new TRotationEventEnd();
	genRandTShape();
	idxActive = 0;
}
GEvent* GTetris::getEvent(int iEventType) {
	return m_events[iEventType];
}

void GTetris::processKeys(const sf::Event& event) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		m_obj[idxActive]->addEvent(getEvent(Events::MoveLeft));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		m_obj[idxActive]->addEvent(getEvent(Events::MoveRight));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		m_obj[idxActive]->addEvent(getEvent(Events::RotateStart));
	}
	if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::W) {
			m_obj[idxActive]->addEvent(getEvent(Events::RotateEnd));
		}
		
	}
}

void GTetris::processEvents(float iTime) {
	for (auto obj: m_obj) {
		obj->update(iTime);
	}
}

void GTetris::postProcess() {
	
}
