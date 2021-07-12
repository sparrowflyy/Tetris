#include "GLoop.h"
#include "TetrisGame/TShape.h"

void GLoop::loop() {


  sf::Clock clock;
  game->init();
  sf::Time dt;
  while (gWin.win->isOpen())
  {
    sf::Event event;
    while (gWin.win->pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        gWin.win->close();
    }
		gWin.win->clear();
    dt = clock.restart();
    game->processKeys();
    game->processEvents(dt.asSeconds());
    for (int i = 0; i < game->m_obj.size(); i++) {
        gWin.draw(game->m_obj[i].get());
    }
    gWin.win->display();
  }
}