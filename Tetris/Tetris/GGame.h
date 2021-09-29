#pragma once
#include "GObj.h"


class GGame
{
public:

	virtual void init() = 0;
	virtual void processKeys(const sf::Event& event) = 0;
	virtual void processEvents(float iTime) = 0;
	virtual void postProcess() = 0;
    virtual ~GGame() { objects.clear(); eventsPool.clear();}

	float frameTime;
	int winWidth;
	int winHeight;
    std::vector<GObj*> objects;
    std::vector<GEvent*> eventsPool;
    friend class GLoop;
};
