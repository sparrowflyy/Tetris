#include "GTetris.h"
#
#include "../GUtils.h"

void GTetris::genRandTShape() {
	//std::shared_ptr<TShape> rndShape = std::make_shared<TShape>(TShape(GUtils::genRandomInt(0, TetrisShapes::numTypes - 1)));
	TShape* rndShape = new TShape(GUtils::genRandomInt(0, TetrisShapes::numTypes - 1));
	m_obj.push_back(rndShape);
}

void GTetris::init() {
	genRandTShape();
	idxActive = 0;
}

void GTetris::processKeys() {
	//m_obj[idxActive]->addEvent(GEventMotion(sf::Vector2f(0, TetrisShapes::rectSize)));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		GEventMotion ev(sf::Vector2f(-TetrisShapes::rectSize, 0));
		m_obj[idxActive]->addEvent(ev);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		GEventMotion ev(sf::Vector2f(TetrisShapes::rectSize, 0));
		m_obj[idxActive]->addEvent(ev);
	}
	
}

void GTetris::processEvents(float iTime) {
	for (auto obj: m_obj) {
		obj->update(iTime);
	}
}

void GTetris::postProcess() {
	
}
