#pragma once
#include <SFML/Graphics.hpp>
#include "GEvent.h"
#include <memory>

class GObj :public sf::Drawable, public sf::Transformable
{
public:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {};
	void addEvent(std::shared_ptr<GEvent> iEvent) { events.push_back(iEvent); }
	virtual void processEvent(int iEventIdx) = 0;
  virtual sf::FloatRect getExtents() const {return  {};} ;
	virtual ~GObj() {
		textures.clear();
		sprites.clear();
		events.clear();
	};

	//index of sprite to draw
	int curIdx = 0;
	int eventIdx = 0;

	std::vector<std::shared_ptr<sf::Texture>> textures {};
	std::vector<std::shared_ptr<sf::Sprite>> sprites {};
	std::vector<std::shared_ptr<GEvent>> events;
};