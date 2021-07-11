#pragma once
#include <SFML/Graphics.hpp>
#include "GEvent.h"
class GObj
{
public:
	GObj(int iParts = 1) : parts(iParts) {}
	GObj(const std::string& iPath) : parts(1) {
		addTexture(iPath);
	}
	GObj(const std::vector<std::string>& iPaths) : parts(1) {
		for (auto path : iPaths) {
			addTexture(path);
		}
	};
	void addTexture(const std::string& iPath)
	{
		m_textures.push_back(std::make_shared<sf::Texture>(sf::Texture()));
		m_textures.back()->loadFromFile(iPath.c_str());
		m_sprites.push_back(std::make_shared<sf::Sprite>(sf::Sprite()));
		m_sprites.back()->setTexture(*m_textures.back());
	}

	virtual const sf::Drawable* getDrawable(int idx) const { return nullptr; }
	void addEvent(const GEvent& iEvent) { m_events.push_back(iEvent); }
	virtual void update(float iTime) {}
	
	virtual ~GObj() {
		m_textures.clear();
		m_sprites.clear();
	};

	//index of sprite to draw
	int curIdx = 0;
	int parts;
	std::vector<std::shared_ptr<sf::Texture>> m_textures {};
	std::vector<std::shared_ptr<sf::Sprite>> m_sprites {};
	std::vector<GEvent> m_events {};
	
};