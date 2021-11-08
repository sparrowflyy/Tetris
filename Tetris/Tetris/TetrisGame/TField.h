#pragma once

#include "../GObj.h"
enum Cell{
    Empty,
    Shape
};
namespace TShapes {
    static const float outlineThick = 0.7;
    static const int numTypes = 7;
    static sf::Vector2i start{ 8,2 };
    static const std::vector<sf::Color> shapeColors {
      sf::Color(255,90,90),  //red
      sf::Color(204,255,151), //yellow
      sf::Color(110,255,102),  //green
      sf::Color(153,153,255), //blue
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
    bool alive = true;
    sf::Color color;
};
class TField final : public GObj {
public:
    TField(int iWinWidth, int iWinHeight);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void processEvent(int iEventIdx) override;
    ~TField() final;
    void checkField();
    void genRandTShape();
    bool isGameOver();
    std::shared_ptr<TShape> nextShape;
    std::shared_ptr<TShape> activeShape;
    int score = 0;

    float rectSize;
private:
    const sf::Color backgroundColor = sf::Color::Transparent;
    void copyRowColors(int iRow, int iDestRow);
    bool checkShape(TShape& iShape);
    void markRect(short i, short j, sf::Color const& iColor = sf::Color::Transparent);
    int getMark(short i, short j);
    bool rotationForbidden = false;
    const int bufferSize = 5;
    int fieldWidth = 16; //16
    int fieldHeight;
    std::vector<std::vector<std::shared_ptr<sf::RectangleShape>>> grid;
};
