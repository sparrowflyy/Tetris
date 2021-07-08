#pragma once
#include <SFML/Graphics.hpp>
class GObj
{
	
public:
	
	GObj(){};
	GObj(const std::string& iPath) {
		addTexture(iPath);
	}
	GObj(const std::vector<std::string>& iPaths) {
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
	virtual void update(float time) = 0;
	//index of sprite to draw
	int curIdx = 0;
	std::vector<std::shared_ptr<sf::Texture>> m_textures;
	std::vector<std::shared_ptr<sf::Sprite>> m_sprites;

	virtual ~GObj() {
		m_textures.clear();
		m_sprites.clear();
	};
};