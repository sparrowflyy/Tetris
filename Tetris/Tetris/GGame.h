#pragma once
#include "GObj.h"


class GGame
{
public:

	virtual void init() = 0;
  virtual void drawObjects(sf::RenderTarget &target, sf::RenderStates states) = 0;
	virtual void processKeys(const sf::Event& event, float iTime) = 0;
	virtual void processEvents(float iTime) = 0;
	virtual void postProcess() = 0;
  virtual ~GGame() noexcept { objects.clear(); eventsPool.clear();}

	float frameTime;
	int winWidth;
	int winHeight;

  std::vector<std::shared_ptr<GEvent>> eventsPool;
  friend class GLoop;
  bool isGameStarted;
  bool isGameOver;
  std::vector<std::shared_ptr<GObj>> objects;
};
