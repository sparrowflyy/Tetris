#include <iostream>
#include <SFML/Graphics.hpp>
#include "GLoop.h"
#include "TetrisGame/GTetris.h"



int main(int argnum, char* argc[], char*argv[] )
{
 /* sf::VideoMode videoMode(320,240);
  sf::RenderWindow window(videoMode,"S");
  sf::Font font;
  font.loadFromFile("/home/nik/c++/Tetris/Tetris/Tetris/TetrisGame/Data/retro.ttf");
  sf::Text text("aboba",font);
  text.setPosition(20,10);
//text.setColor(Color::Red);

  while (window.isOpen())
  {
    window.clear();
    window.draw(text);
    window.display();

    sf::Event event;
    while (window.pollEvent(event))
    {
      if ( (event.type == sf::Event::Closed) ||
           ((event.type == sf::Event::KeyPressed) && (event.key.code==sf::Keyboard::Escape)) )
        window.close();

    }
  }*/
  GTetris* game = new GTetris();
  GLoop gLoop(game);
  gLoop.loop();
  return 0;
}
