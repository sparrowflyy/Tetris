#pragma once
#include "GGame.h"
class GLoop final
{
public:
	GLoop(GGame* iGame): game(std::move(iGame)){}
	void loop();
	~GLoop() = default;

private:
	std::unique_ptr<GGame> game;
	
};