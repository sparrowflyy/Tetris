#include <SFML/Graphics.hpp>
#include "GLoop.h"
#include "./TetrisGame/GTetris.h"
//int WinMain()
//{
//	
//  GTetris* game = new GTetris();
//  GLoop gLoop(game);
//  gLoop.loop();
//
//  return 0;
//}

int main()
{

  GTetris* game = new GTetris();
  GLoop gLoop(game);
  gLoop.loop();

  return 0;
}