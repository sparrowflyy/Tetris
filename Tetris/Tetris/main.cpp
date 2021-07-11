#include <SFML/Graphics.hpp>
#include "GLoop.h"
int WinMain()
{
	
  GLoop gLoop;
  gLoop.loop();
  //sf::RenderWindow window(sf::VideoMode(500, 650), "SFML works!");
  //sf::CircleShape shape(100.f);
  //shape.setFillColor(sf::Color::Green);
 
  //while (window.isOpen())
  //{
  //  sf::Event event;
  //  while (window.pollEvent(event))
  //  {
  //    if (event.type == sf::Event::Closed)
  //      window.close();
  //  }

  //  window.clear();
  //  window.draw(shape);
  //  window.display();
  //}

  return 0;
}