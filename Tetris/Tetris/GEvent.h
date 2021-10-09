#pragma once
#include <SFML/Graphics.hpp>
class GEvent
{
public:
	enum EventType
	{
		NullEvent,
		MotionStart,
    MotionEnd,
		Intersection,
		Force,
		RotationStart,
		RotationEnd
	};
	explicit GEvent(int iType = EventType::NullEvent) : type(iType) {}
	int type;
  ~GEvent() = default;
};


template <typename T>
class GEventMotion: public GEvent
{
public:
	explicit GEventMotion(const sf::Vector2<T>& iMotion) : GEvent(EventType::MotionStart), motion(iMotion) {}
	const sf::Vector2<T>& getMotion() const { return motion; }
    ~GEventMotion() = default;
private:
	sf::Vector2<T> motion;
};