#include "GLoop.h"
#include "TetrisGame/TShape.h"

void GLoop::loop() {

  Tetris::TShape line(Tetris::ShapeType::Line);
	
  m_obj.push_back(std::make_shared<Tetris::TShape>(line));
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