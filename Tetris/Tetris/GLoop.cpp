#include "GLoop.h"


void GLoop::loop() {
  sf::RenderWindow window(sf::VideoMode(game->winWidth, game->winHeight), "Tetris");
  sf::Clock clock;
  float dt = 0;
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed) {
        window.close();
        return;
      }
    }
    window.clear();
    sf::Time elapsedTime = clock.getElapsedTime();
    dt += elapsedTime.asSeconds();
    game->timer.addTimeTickS(dt);
    game->processKeys(event);
    if (dt >= frameTime) {
      game->processEvents();
      dt = 0;
      clock.restart();
    }
    game->postProcess();
    game->drawObjects(window,sf::RenderStates::Default);

    window.display();


  }
}