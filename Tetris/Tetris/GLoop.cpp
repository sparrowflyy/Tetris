#include "GLoop.h"
#include "TetrisGame/TShape.h"

void GLoop::loop() {
  sf::RenderWindow window(sf::VideoMode(500, 600), "SFML works!");
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);
  TShape T(TetrisShapes::T);
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
      //T.draw(window,sf::RenderStates::Default);
        //gWin.draw(game->m_obj[i].get());
    }
    window.draw(shape);
    window.display();
  }

  //return 0;
  //sf::Clock clock;
  //sf::RenderWindow window(sf::VideoMode(500, 650), "SFML works!");
  //game->init();
  //sf::Time dt;
  //sf::CircleShape shape(100.f);
  //while (window.isOpen())
  //{
  //  sf::Event event;
  //  while (window.pollEvent(event))
  //  {
  //    if (event.type == sf::Event::Closed)
  //      window.close();
  //  }
  //  window.clear();
  //  dt = clock.restart();
  //  game->processKeys();
  //  game->processEvents(dt.asSeconds());
  //  //for (int i = 0; i < game->m_obj.size(); i++) {
  //  //  game->m_obj[i]->draw(window,sf::RenderStates::Default);
  //  //    //gWin.draw(game->m_obj[i].get());
  //  //}
  //  window.draw(shape);
  //  window.display();
  //}
}