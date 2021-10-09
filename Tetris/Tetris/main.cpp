#include <iostream>
#include <SFML/Graphics.hpp>
#include "GLoop.h"
#include "TetrisGame/GTetris.h"



int main(int argnum, char* argc[], char*argv[] )
{
  GTetris* game = new GTetris();
  GLoop gLoop(game);
  gLoop.loop();
  return 0;
}
