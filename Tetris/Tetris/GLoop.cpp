#include "GLoop.h"
#include "TetrisGame/TShape.h"

void GLoop::loop() {
  sf::RenderWindow window(sf::VideoMode(500, 600), "Tetris");
  game->init();
  sf::Clock clock;
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    sf::Time dt = clock.getElapsedTime();
    window.clear();
  
      
    if (dt.asSeconds() >= game->frameTime) {
      game->processKeys();
      game->processEvents(dt.asSeconds());
     
		  clock.restart();
    	
    }
    for (int i = 0; i < game->m_obj.size(); i++) {
      game->m_obj[i]->draw(window, sf::RenderStates::Default);
    }
    window.display();
  }
}