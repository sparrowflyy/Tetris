#include <iostream>
#include <SFML/Graphics.hpp>
#include "GLoop.h"
#include "TetrisGame/GTetris.h"



int main()
{
  GTetris* game = new GTetris();
  GLoop gLoop(game);
  gLoop.loop();

  return 0;
}
