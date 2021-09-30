#pragma once
#include "../GGame.h"
#include "../GObjIntersector.h"

class TRotationEventStart final: public GEvent
{
public:
	TRotationEventStart() : GEvent(GEvent::EventType::RotationStart){}
	~TRotationEventStart() final = default;
};
class TRotationEventEnd final : public GEvent
{
public:
	TRotationEventEnd() : GEvent(GEvent::EventType::RotationEnd) {}
	~TRotationEventEnd() final = default;
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
    //TODO: correct width height
	explicit GTetris(int iWinWidth = 506, int iWinHeight = 596, float iFrameTime = 1e-6);
	void init() override;
	void processKeys(const sf::Event& event) override;
	void processEvents(float iTime) override;
	void postProcess() override;
	~GTetris() final;
private:
	enum Events
	{
		MoveLeft,
		MoveRight,
        MoveDown,
		RotateStart,
		RotateEnd
	};
    const int fieldIdx = 0;
	float elapsedTime = 0.0;
	const float fallTime = 1.0;
};