#pragma once
#include "GObj.h"


class GGame
{
public:
	typedef std::vector<GObj*> GData;
	virtual void init() = 0;
	virtual void processKeys() = 0;
	virtual void processEvents(float iTime) = 0;
	virtual void postProcess() = 0;
	friend class GLoop;
	virtual ~GGame() { m_obj.clear(); }
	float frameTime;
	GData m_obj;
};
