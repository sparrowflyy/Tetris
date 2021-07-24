#pragma once
#include "../GGame.h"
#include "TShape.h"

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
	
}
class GTetris : public GGame
{
public:
	GTetris() { frameTime = 1e-10;};
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
	int idxActive = 0;
	std::vector<GEvent*> m_events;
	void genRandTShape();
};