#include "GTetris.h"
#
#include "../GUtils.h"

void GTetris::genRandTShape() {
	m_obj.push_back(std::make_shared<GObj>(TShape(GUtils::genRandomInt(0, TetrisShapes::numTypes-1))));
}

void GTetris::init() {
	genRandTShape();
	activeShape = m_obj[0];
}

void GTetris::processKeys() {
	activeShape->addEvent(GEventMotion(sf::Vector2f(0, TetrisShapes::rectSize)));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		GEventMotion ev(sf::Vector2f(-TetrisShapes::rectSize, 0));
		activeShape->addEvent(ev);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		GEventMotion ev(sf::Vector2f(TetrisShapes::rectSize, 0));
		activeShape->addEvent(ev);
	}
	
}

void GTetris::processEvents(float iTime) {
	for (auto obj: m_obj) {
		obj->update(iTime);
	}
}

void GTetris::postProcess() {
	
}
