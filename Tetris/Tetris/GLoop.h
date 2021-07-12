#pragma once
#include "GWindow.h"

#include "GGame.h"
class GLoop final
{
public:
	GLoop(GGame* iGame): game(std::move(iGame)){}
	void loop();
	~GLoop() = default;

private:
	GWindow gWin {};
	std::unique_ptr<GGame> game;
	
};