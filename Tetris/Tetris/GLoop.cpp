#include "GLoop.h"
#include "TetrisGame/TShape.h"

void GLoop::loop() {
  sf::RenderWindow window(sf::VideoMode(500, 600), "Tetris");
  game->init();
  sf::Clock clock;
  float dt = 0;
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    sf::Time elapsedTime = clock.getElapsedTime();
    dt += elapsedTime.asSeconds();
    window.clear();
    game->processKeys(event);
    if (dt >= game->frameTime) {
     
      game->processEvents(dt);
      dt = 0;
		  clock.restart();
    	
    }
    for (int i = 0; i < game->m_obj.size(); i++) {
      game->m_obj[i]->draw(window, sf::RenderStates::Default);
    }
    window.display();
  }
}