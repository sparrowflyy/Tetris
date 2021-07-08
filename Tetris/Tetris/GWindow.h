#pragma once
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include "GObj.h"

class GWindow final 
{
public:
	GWindow();
	GWindow(int iWeight, int iHeight, std::string& iTitle);
	void draw(const GObj& iGameObj) const;
	~GWindow() = default;
	friend class GLoop;
private:
	std::unique_ptr<sf::RenderWindow> win;
};