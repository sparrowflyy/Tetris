#pragma once
#include "../GGame.h"
#include "TShape.h"
#include "../GObjIntersector.h"

class TRotationEventStart: public GEvent
{
public:
	TRotationEventStart() : GEvent(GEvent::EventType::RotationStart){}
	~TRotationEventStart() {};
};
class TRotationEventEnd : public GEvent
{
public:
	TRotationEventEnd() : GEvent(GEvent::EventType::RotationEnd) {}
	~TRotationEventEnd() {};
};

namespace Tetris
{
	static const sf::Vector2f left(-1, 0);
	static const sf::Vector2f right(1, 0);
	static const sf::Vector2f down(0, 1);
	static const sf::Vector2f up(1, 0);
	
}
class GTetris : public GGame
{
public:
	GTetris(int iWinWidth = 500, int iWinHeight = 600, float iFrameTime = 1e-6);
	void init() override;
	void processKeys(const sf::Event& event) override;
	void processEvents(float iTime) override;
	void postProcess() override;
	~GTetris() { m_events.clear(); }
private:
	enum Events
	{
		MoveLeft,
		MoveRight,
		RotateStart,
		RotateEnd
	};
	GEvent* getEvent(int iEventType);
	void genRandTShape();
	GObjIntersector intersector;
	int idxActive = 0;
	float elapsedTime = 0.0;
	const float fallTime = 0.5;
	std::vector<GEvent*> m_events;

};