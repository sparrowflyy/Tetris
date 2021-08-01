#pragma once

#include "../GObj.h"

class TField : public GObj
{
public:
	TField(int iWinWidth, int iWinHeight);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  void processEvent(float iTime, int iEventIdx) override{};
	void revertLastEvent() override {};
	sf::FloatRect getExtents() const  override { return sf::FloatRect(); };
	~TField();
private:
	std::vector<sf::RectangleShape> m_grid;
};