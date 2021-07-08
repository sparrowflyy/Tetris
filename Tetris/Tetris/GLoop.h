#pragma once
#include "GWindow.h"
#include "GData.h"

class GLoop final
{
public:
	GLoop();
	void loop();
	~GLoop() = default;
private:
	GWindow gWin;
	GData data;
};