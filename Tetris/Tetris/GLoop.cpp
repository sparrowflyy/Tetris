#include "GLoop.h"
#include "TetrisGame/TShape.h"

void GLoop::loop() {
  sf::RenderWindow window(sf::VideoMode(500, 600), "Tetris");
  game->init();
  float gameSpeed = 1e-2;
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
  
      
    if (dt.asSeconds() >= gameSpeed) {
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