#include "GWindow.h"

GWindow::GWindow() {
	win = std::make_unique<sf::RenderWindow>(sf::VideoMode(500, 650), "Tetris");
}

GWindow::GWindow(int iWidth, int iHeight, std::string& iTitle) {
	win = std::make_unique<sf::RenderWindow>(sf::VideoMode(iWidth, iHeight), iTitle.c_str());
}

void GWindow::draw(const GObj* iGameObj) const {
	for (int i = 0; i < iGameObj->parts; i++)
	{
		win->draw(*iGameObj->getDrawable(i));
	}
}