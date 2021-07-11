#pragma once
#include "GWindow.h"


class GLoop final
{
public:
	GLoop();
	void loop();
	~GLoop() = default;
private:
	GWindow gWin;
	std::vector<std::shared_ptr<GObj>> m_obj;
};