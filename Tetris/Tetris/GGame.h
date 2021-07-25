#pragma once
#include "GObj.h"


class GGame
{
public:
	typedef std::vector<GObj*> GData;
	virtual void init() = 0;
	virtual void processKeys(const sf::Event& event) = 0;
	virtual void processEvents(float iTime) = 0;
	virtual void postProcess() = 0;
	friend class GLoop;
	virtual ~GGame() { m_obj.clear(); }
	float m_frameTime;
	int m_winWidth;
	int m_winHeight;
	GData m_obj;
};
