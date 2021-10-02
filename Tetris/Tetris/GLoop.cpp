#include "GLoop.h"


void GLoop::loop() {
  sf::RenderWindow window(sf::VideoMode(game->winWidth, game->winHeight), "Tetris");
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
    game->processKeys(event,dt);
    if (dt >= game->frameTime) {
      game->processEvents(dt);
      dt = 0;
		  clock.restart();
    }
    for (auto* obj : game->objects) {
      obj->draw(window, sf::RenderStates::Default);
    }
    window.display();
  }
}