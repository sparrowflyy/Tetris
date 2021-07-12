#include <SFML/Graphics.hpp>
#include "GLoop.h"
#include "./TetrisGame/GTetris.h"
int WinMain()
{
  GTetris game;
  GLoop gLoop(&game);
  gLoop.loop();

  return 0;
}