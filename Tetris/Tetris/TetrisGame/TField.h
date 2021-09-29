#pragma once

#include "../GObj.h"
enum Cell{
    Empty,
    Shape
};
namespace TShapes {
    static const int rectSize = 30;
    static const float outlineThick = 2;
    static const int numTypes = 7;
    static sf::Vector2i start{ 10,2 };
    static const std::vector<sf::Color> shapeColors {
            sf::Color(153,0,153),  //purple
            sf::Color(204,255,51), //yellow
            sf::Color(0,255,102),  //green
            sf::Color(151,53,255), //blue
            sf::Color(255,51,153)  //pink
    };
    enum Type
    {
        I,
        Z,
        S,
        O,
        T,
        J,
        L
    };
}
class TShape final{
public:
    TShape(int type, const sf::Vector2i& iMaxPoint = TShapes::start);
    const sf::Color& getRandColor();
    void init();
    void initI();
    void initZ();
    void initS();
    void initO();
    void initT();
    void initJ();
    void initL();
    int type;
private:
    sf::Vector2i maxPoint;
    std::vector<std::pair<short,short>> indices;
    bool rotated = false;
};
class TField final : public GObj {
    public:
        TField(int iWinWidth, int iWinHeight);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void processEvent(float iTime, int iEventIdx) override;
        void revertLastEvent() override;
        ~TField() final;
    private:
        void genRandTShape();
/*        void moveShape(const sf::Vector2i& iMotion);
        void rotateShape(bool iClockWise = true);*/
        void markRect(short i, short j, sf::Color const& iColor = sf::Color::Transparent);
        int getMark(short i, short j);
        int idxActive = 0;
        short fieldWidth;
        short fieldHeight;
        std::vector<sf::RectangleShape> grid;
        std::vector<TShape> shapes;
    };
