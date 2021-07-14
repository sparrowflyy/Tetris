#include "GTetris.h"
#
#include "../GUtils.h"

void GTetris::genRandTShape() {
	//TShape* rndShape = new TShape(GUtils::genRandomInt(0, TetrisShapes::numTypes - 1));
	TShapeT* rndShape = new TShapeT();
	m_obj.push_back(rndShape);
}

void GTetris::init() {
	genRandTShape();
	idxActive = 0;
}

void GTetris::processKeys() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		m_obj[idxActive]->addEvent(new GEventMotion(Tetris::left * float(TetrisShapes::rectSize)));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		m_obj[idxActive]->addEvent(new GEventMotion(Tetris::right * float(TetrisShapes::rectSize)));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		m_obj[idxActive]->addEvent(new GEventMotion({0,0},90));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
		m_obj[idxActive]->addEvent(new GEventMotion({ 0,0 }, -90));
	}
	
}

void GTetris::processEvents(float iTime) {
	for (auto obj: m_obj) {
		obj->update(iTime);
	}
}

void GTetris::postProcess() {
	
}
