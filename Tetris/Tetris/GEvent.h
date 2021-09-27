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
		Force,
		RotationStart,
		RotationEnd
	};
	GEvent(int iType = EventType::NullEvent) : type(iType) {}
	
	int type;
	virtual ~GEvent() {}
};


template <typename T>
class GEventMotion: public GEvent
{
public:
	GEventMotion(const sf::Vector2<T>& iMotion) : GEvent(EventType::Motion), motion(iMotion) {}
	const sf::Vector2<T>& getMotion() const { return motion; }
  ~GEventMotion() {}
private:
	sf::Vector2<T> motion;
};