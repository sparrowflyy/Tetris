#include "GTetris.h"
#
#include <iostream>
#include "TField.h"
#include "../GUtils.h"

GTetris::GTetris(int iWinWidth, int iWinHeight, float iFrameTime):intersector(iWinWidth,iWinHeight) {
	m_winWidth = iWinWidth;
	m_winHeight = iWinHeight;
	m_frameTime = iFrameTime;
	auto* field = new TField(iWinWidth, iWinHeight);
	m_obj.push_back(field);
}

void GTetris::genRandTShape() {
	idxActive = m_obj.size();
	auto* rndShape = new TShape(GUtils::genRandomInt(0, TetrisShapes::numTypes - 1));
	//TShape* rndShape = new TShape(TetrisShapes::J);
	m_obj.push_back(rndShape);
}

void GTetris::init() {
	m_events.resize(5);

	m_events[Events::MoveLeft] = new GEventMotion(Tetris::left);
	m_events[Events::MoveRight] = new GEventMotion(Tetris::right);
    m_events[Events::MoveDown] = new GEventMotion(Tetris::right);
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        m_obj[idxActive]->addEvent(getEvent(Events::MoveDown));
    }
	if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::W) {
			m_obj[idxActive]->addEvent(getEvent(Events::RotateEnd));
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		m_obj[idxActive]->addEvent(getEvent(Events::RotateStart));
	}

}

void GTetris::processEvents(float iTime) {
	elapsedTime += iTime;
	if (elapsedTime > fallTime) {
		m_obj[idxActive]->addEvent(new GEventMotion(Tetris::down));
		elapsedTime = 0.0;
	}
	for (auto & objIdx : m_obj) {
		auto* curShape = (TShape*)objIdx;
		for (int i = 0; i < curShape->m_events.size(); i++) {
			curShape->processEvent(iTime, i);
		}
	objIdx->m_events.clear();
	}
}
void GTetris::postProcess() {
}
