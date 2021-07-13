#pragma once
#include "../GGame.h"
#include "TShape.h"

namespace Tetris
{
	static const sf::Vector2f left(-1, 0);
	static const sf::Vector2f right(1, 0);
	static const sf::Vector2f down(0, 1);
	
}
class GTetris : public GGame
{
public:
	GTetris() {}
	void init() override;
	void processKeys() override;
	void processEvents(float iTime) override;
	void postProcess() override;
	~GTetris() {}
private:
	int idxActive = 0;
	void genRandTShape();
};