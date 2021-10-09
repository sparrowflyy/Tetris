#pragma once
#include "../GGame.h"
#include "../GObjIntersector.h"

class TRotationEventStart final: public GEvent
{
public:
	TRotationEventStart() : GEvent(GEvent::EventType::RotationStart){}
	~TRotationEventStart()  = default;
};
class TRotationEventEnd final : public GEvent
{
public:
	TRotationEventEnd() : GEvent(GEvent::EventType::RotationEnd) {}
	~TRotationEventEnd() = default;
};

namespace Tetris
{
	static const sf::Vector2i left(-1, 0);
	static const sf::Vector2i right(1, 0);
	static const sf::Vector2i down(0, 1);
	static const sf::Vector2i up(0, -1);
}

class GTetris final: public GGame
{
public:
	explicit GTetris(int iWinWidth = 400, int iWinHeight = 500, float iFrameTime = 1e-6);
	void init() override;
	void processKeys(const sf::Event& event, float iTime) override;
	void processEvents(float iTime) override;
	void postProcess() override;
	~GTetris() ;
private:
	enum Events
	{
		MoveLeft,
		MoveRight,
    MoveDown,
    MoveEnd,
		RotateStart,
		RotateEnd
	};
	float elapsedTime = 0.0;
	float fallTime = 0.5;
  const float motionTime = 0.075;
  const int fieldIdx = 1;
};