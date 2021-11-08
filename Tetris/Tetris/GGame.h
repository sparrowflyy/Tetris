#pragma once
#include "GObj.h"
#include "GTimer.h"

class GGame
{
public:

	virtual void init() = 0;
  virtual void drawObjects(sf::RenderTarget &target, sf::RenderStates states) = 0;
	virtual void processKeys(const sf::Event& event) = 0;
	virtual void processEvents() = 0;
	virtual void postProcess() = 0;
  virtual ~GGame() noexcept { objects.clear(); eventsPool.clear();}
  GTimer timer;
	int winWidth;
	int winHeight;

  std::vector<std::shared_ptr<GEvent>> eventsPool;
  friend class GLoop;
  bool isGameStarted;
  bool isGameOver;
  std::vector<std::shared_ptr<GObj>> objects;
};
