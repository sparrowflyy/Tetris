#pragma once

#include "../GObj.h"
enum Cell{
    Empty,
    Shape
};
namespace TShapes {
    static const int rectSize = 30;
    static const float outlineThick = 0.7;
    static const int numTypes = 7;
    static sf::Vector2i start{ 5,2 };
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

    void move(const sf::Vector2i& iMotion);
    void rotate();
    void init();
    void initI();
    void initZ();
    void initS();
    void initO();
    void initT();
    void initJ();
    void initL();
    int type;
    sf::Vector2i center;
    std::vector<std::pair<int,int>> indices;
    bool rotating = false;
    bool moving = false;
    sf::Color color;
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
        //TODO: add additional parameter - real activeShape before all events to deduct what's happen
        bool checkShape(const TShape& iShape);
        void markRect(short i, short j, sf::Color const& iColor = sf::Color::White);
        int getMark(short i, short j);
        int fieldWidth = 15;
        int fieldHeight ;
        std::vector<std::vector<sf::RectangleShape>> grid;
        std::vector<TShape> shapes;
        const float motionTime = 0.1;
    };
