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
	explicit GEvent(int iType = EventType::NullEvent) : type(iType) {}
	
	int type;
	virtual ~GEvent() = default;
};


template <typename T>
class GEventMotion: public GEvent
{
public:
	explicit GEventMotion(const sf::Vector2<T>& iMotion) : GEvent(EventType::Motion), motion(iMotion) {}
	const sf::Vector2<T>& getMotion() const { return motion; }
    ~GEventMotion() = default;
private:
	sf::Vector2<T> motion;
};