#include "GTetris.h"
#
#include <iostream>

#include "../GUtils.h"

GTetris::GTetris(int iWinWidth, int iWinHeight, float iFrameTime):intersector(iWinWidth,iWinHeight) {
	m_winWidth = iWinWidth;
	m_winHeight = iWinHeight;
	m_frameTime = iFrameTime;
	
}

void GTetris::genRandTShape() {
	idxActive = m_obj.size();
	TShape* rndShape = new TShape(GUtils::genRandomInt(0, TetrisShapes::numTypes - 1));
	//TShape* rndShape = new TShape(TetrisShapes::J);
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
		m_obj[idxActive]->addEvent(new GEventMotion(Tetris::down*float(500.00)/* * float(TetrisShapes::rectSize) / iTime*/));
		elapsedTime = 0.0;
	}
	for (int objIdx = 0; objIdx < m_obj.size(); objIdx++) {
		TShape* curShape = (TShape*)m_obj[objIdx];
		bool glued = objIdx != idxActive;
		for (int i = 0; i < curShape->m_events.size(); i++) {
			if (glued) break;
			curShape->processEvent(iTime, i);
			sf::FloatRect objBox = m_obj[objIdx]->getExtents();
			sf::FloatRect interBox;
			if (intersector.intersectObjBoxWindow(curShape,interBox)) {
				if (interBox.top < objBox.top + objBox.height) {
					curShape->moveShape(Tetris::up * interBox.height);
					glued = true;
					genRandTShape();
					break;
				}
				curShape->revertLastEvent();
				continue;
			}
			sf::FloatRect otherBox;
			for (int j = 0; j < m_obj.size(); j++) {
				if (objIdx == j)
					continue;
				TShape* otherShape = (TShape*)m_obj[j];
				otherBox = otherShape->getExtents();
				if (GObjIntersector::intersectObjBoxes(curShape, otherShape, interBox)) {
					double width = interBox.width;
					std::cout << "interBox.width: " << interBox.width << std::endl;
					RectInterInfo interInfo = curShape->intersectShape(otherShape, interBox);
				
					if (interInfo.intersection && (objBox.top < otherBox.top) && width >= TetrisShapes::rectSize ) {
						float dy = fabs(TetrisShapes::rectSize - fabs(interInfo.myRectPos.y - interInfo.otherRectPos.y));
						curShape->moveShape(Tetris::up * (dy- TetrisShapes::outlineThick));
						glued = true;
						genRandTShape();
						break;
					}
					else {
						m_obj[objIdx]->revertLastEvent();
						break;
					}
				}
					
			}
		}
	m_obj[objIdx]->m_events.clear();
	}

}


void GTetris::postProcess() {
	
}
