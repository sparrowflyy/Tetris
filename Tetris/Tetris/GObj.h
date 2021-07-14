#pragma once
#include <SFML/Graphics.hpp>
#include "GEvent.h"
class GObj :public sf::Drawable, public sf::Transformable
{
public:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {};
	void addEvent(const GEvent* iEvent) { m_events.push_back(iEvent); }
	virtual void update(float iTime) = 0;
	virtual ~GObj() {
		m_textures.clear();
		m_sprites.clear();
		m_events.clear();
	};

	//index of sprite to draw
	int curIdx = 0;
	int parts;
	std::vector<std::shared_ptr<sf::Texture>> m_textures {};
	std::vector<std::shared_ptr<sf::Sprite>> m_sprites {};
	std::vector<const GEvent*> m_events;
	
};