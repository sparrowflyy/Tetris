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
    for (int i = 0; i < m_obj.size(); i++)
    {
      gWin.draw(*m_obj[i]);
    }
    gWin.win->display();
  }
}