#include "GLoop.h"
#include "TetrisGame/TShape.h"

void GLoop::loop() {
  sf::RenderWindow window(sf::VideoMode(500, 600), "Tetris");
  game->init();
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();
    game->processKeys();
		game->processEvents(1);
    for (int i = 0; i < game->m_obj.size(); i++) {
      game->m_obj[i]->draw(window, sf::RenderStates::Default);
    }
    window.display();
  }
}