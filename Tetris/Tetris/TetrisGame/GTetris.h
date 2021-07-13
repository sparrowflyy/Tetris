#pragma once
#include "../GGame.h"
#include "TShape.h"

namespace Tetris
{

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