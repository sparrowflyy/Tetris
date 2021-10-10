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
    TextUpdate
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

class GEventTextUpdate : public GEvent {
public:
    GEventTextUpdate(const std::string& iString) : GEvent(GEvent::EventType::TextUpdate),string(iString){};
    ~GEventTextUpdate()  = default;
    void setString(const std::string& iString) {string = iString;};
    std::string string;
};
