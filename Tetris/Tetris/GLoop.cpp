#include "GLoop.h"

GLoop::GLoop()
{
	
}
void GLoop::loop() {

  while (gWin.win->isOpen())
  {
    sf::Event event;
    while (gWin.win->pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        gWin.win->close();
    }

    gWin.win->clear();
    //gWin.draw(shape);
    gWin.win->display();
  }
}