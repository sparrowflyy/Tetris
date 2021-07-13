#pragma once
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include "GObj.h"


class GWindow final 
{
public:
	GWindow(): win(new sf::RenderWindow(sf::VideoMode(500, 650), "Tetris")) {}
	GWindow(int iWeight, int iHeight, std::string& iTitle):
		win(new sf::RenderWindow(sf::VideoMode(iWeight, iHeight),iTitle.c_str())) {}
	void draw(const GObj* iGameObj) const;
	~GWindow() = default;
	friend class GLoop;
private:
	std::unique_ptr<sf::RenderWindow> win;
};