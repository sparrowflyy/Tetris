#include <SFML/Graphics.hpp>

int WinMain()
{
  sf::RenderWindow window(sf::VideoMode(500, 650), "SFML works!");
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);
 
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();
    window.draw();
    window.display();
  }

  return 0;
}