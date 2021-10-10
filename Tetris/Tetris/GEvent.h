#pragma once
#include <SFML/Graphics.hpp>
class GEvent
{
public:
	enum EventType
	{
		DefaultEvent,
		MotionStart,
    MotionEnd,
		Intersection,
		Force,
		RotationStart,
		RotationEnd,
    Text
	};
	explicit GEvent(int iType = EventType::DefaultEvent) : type(iType) {}
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

class GEventText: public GEvent {
public:
    GEventText(const std::string& iString) : GEvent(GEvent::EventType::Text),string(iString){};
    ~GEventText()  = default;
    void setString(const std::string& iString) {string = iString;};
    std::string string;
};
