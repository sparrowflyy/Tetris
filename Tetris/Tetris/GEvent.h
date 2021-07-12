#pragma once
#include <SFML/Graphics.hpp>
class GEvent
{
public:
	enum EventType
	{
		NullEvent,
		Motion,
		Intersection,
		Force
	};
	GEvent(int iType = EventType::NullEvent) : type(iType) {}
	
	int type;
	virtual ~GEvent() {}
};

class GEventMotion: public GEvent
{
public:
	GEventMotion(const sf::Vector2f& iMotion, float iRotAng = 0.0) : GEvent(EventType::Motion), motion(iMotion), angle(iRotAng) {}
	const sf::Vector2f& getMotion() const { return motion; }
	float getAngle() const { return angle; }
  ~GEventMotion() {}
private:
	sf::Vector2f motion;
	float angle;
};