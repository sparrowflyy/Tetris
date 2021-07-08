#pragma once
#include "../GObj.h"

class TShape : public GObj
{
public:
	TShape();
	void update(float time) override;

private:
	std::vector<std::shared_ptr<sf::RectangleShape>> m_rects;
};

