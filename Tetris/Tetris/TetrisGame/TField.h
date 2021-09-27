#pragma once

#include "../GObj.h"
enum Cell{
    Empty,
    Shape
};
class TField : public GObj {
    public:
        TField(int iWinWidth, int iWinHeight);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void processEvent(float iTime, int iEventIdx) override{};
        void revertLastEvent() override {};
        sf::FloatRect getExtents() const  override { return sf::FloatRect(); };

        void markRect(short i, short j, sf::Color const& iColor = sf::Color::Transparent);
        int getMark(short i, short j);
        ~TField();
    private:
        std::vector<sf::RectangleShape> m_grid;
        short m_blockWidth;
        short m_blockHeight;
    };
