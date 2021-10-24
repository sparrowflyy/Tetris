//
// Created by nik on 10.10.2021.
//

#ifndef TETRIS_TWIDGETSCORE_H
#define TETRIS_TWIDGETSCORE_H

#include "../GObj.h"
#include "TField.h"

class TWidgetScore: public GObj {
public:
    TWidgetScore(int iLeft, int iTop, int iWidth, int iHeight, float iRectSize);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void processEvent(float iTime, int iEventIdx) override;
    void revertLastEvent() override {};
    void setNextTShape(std::shared_ptr<TShape> iNextShape);
    ~TWidgetScore() final = default;
private:
    void markNextShape();
    float rectSize;
    float squareFieldSize;
    std::shared_ptr<TShape> nextShape;
    std::vector<std::vector<std::shared_ptr<sf::RectangleShape>>> miniGrid;
    const int fontSize = 24;
    std::vector<sf::Text> texts;
    sf::IntRect rect;
    sf::Font font;
    //TODO: add proper filename
    const std::string fontFilename = "/home/nik/c++/Tetris/Tetris/Tetris/TetrisGame/Data/retro.ttf";
};


#endif //TETRIS_TWIDGETSCORE_H
